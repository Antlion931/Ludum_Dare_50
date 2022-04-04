#include <SFML/Graphics.hpp>
#include <cmath>

#include "Toolkit.hpp"
#include <SFML/System/Vector2.hpp>

bool clamp(sf::RectangleShape a, sf::Vector2f b)
{
	sf::Vector2f size = a.getSize();
	size.x *= a.getScale().x;
	size.y *= a.getScale().y;
	sf::Vector2f position = a.getPosition();

	return b.x <= position.x + size.x &&
		   b.x >= position.x &&
		   b.y <= position.y + size.y &&
		   b.y >= position.y;
}

bool clamp(sf::RectangleShape a, sf::Vector2i b)
{
	sf::Vector2f size = a.getSize();
	size.x *= a.getScale().x;
	size.y *= a.getScale().y;
	sf::Vector2f position = a.getPosition();

	return b.x <= position.x + size.x &&
		b.x >= position.x &&
		b.y <= position.y + size.y &&
		b.y >= position.y;
}

float dot(const sf::Vector2f a, const sf::Vector2f b)
{
	return a.x*b.x + a.y*b.y;
}

sf::Transformable combineTransforms(const sf::Transformable &parent, const sf::Transformable &child)
{
	sf::Transformable result;
	result.setScale({parent.getScale().x*child.getScale().x,parent.getScale().y*child.getScale().y});
	result.setRotation(parent.getRotation() + child.getRotation());
	result.setPosition(parent.getTransform() * child.getPosition());
	return result;
}

std::ostream& operator<< (std::ostream& out, sf::Vector2f const& vec)
{
	return out << vec.x << " " << vec.y;
}

float length(const sf::Vector2f a) 
{
	return std::sqrt(a.x * a.x + a.y * a.y);
}

float length_squared(const sf::Vector2f a) 
{
	return a.x * a.x + a.y * a.y;
}

float clamp(float a, float b, float t)
{
	if(t > b) return b;
	if(t < a) return a;
	return t;
}

sf::Vector2f closestPointToLine(sf::Vector2f A, sf::Vector2f B, sf::Vector2f P)
{
	sf::Vector2f A_to_P = P - A;
	sf::Vector2f A_to_B = B - A;

	float from_A_to_proj = dot(A_to_B, A_to_P) / length_squared(A_to_B);

	return A + A_to_B * clamp(0,1,from_A_to_proj);
}

sf::Vector2f norm(const sf::Vector2f a)
{
	return a / length(a);
}



/// =========================================================================
/// RANDOM POINT GENERATION UTILS
/// =========================================================================

bool isInRectangle(sf::Vector2f vec, float YtoX)
{
	return vec.x >= 0 && vec.y >= 0 && vec.x <= 1 && vec.y <= YtoX;
}

bool isInCircle(sf::Vector2f vec)
{
	const float fx = vec.x - 0.5f;
	const float fy = vec.y - 0.5f;
	return ( fx*fx + fy*fy ) <= 0.25f;
}

float getDistance( const sf::Vector2f& P1, const sf::Vector2f& P2 )
{
	return sqrt( ( P1.x - P2.x ) * ( P1.x - P2.x ) + ( P1.y - P2.y ) * ( P1.y - P2.y ) );
}

sf::Vector2f imageToGrid( const sf::Vector2f& P, float cellSize )
{
	return sf::Vector2f( ( int )( P.x / cellSize ), ( int )( P.y / cellSize ) );
}

sf::Vector2f popRandom( std::vector<sf::Vector2f>& points)
{
	std::random_device rand;
	std::uniform_int_distribution<> dist(0, points.size()-1);
	const int idx = dist(rand);
	const sf::Vector2f p = points[ idx ];
	points.erase( points.begin() + idx );
	return p;
}

sf::Vector2f generateRandomPointAround( const sf::Vector2f& p, float minDist)
{
	std::random_device rand;
	std::uniform_real_distribution<> dist(0,1);
	// start with non-uniform distribution
	const float R1 = dist(rand);
	const float R2 = dist(rand);

	// radius should be between MinDist and 2 * MinDist
	const float radius = minDist * ( R1 + 1.0f );

	// random angle
	const float angle = 2 * 3.141592653589f * R2;

	// the new point is generated around the point (x, y)
	const float x = p.x + radius * cos( angle );
	const float y = p.y + radius * sin( angle );

	return sf::Vector2f( x, y );
}


struct Grid
{
	Grid( int w, int h, float cellSize )
	: w_( w )
	, h_( h )
	, cellSize_( cellSize )
	{
		grid_.resize( w );
		for ( auto i = grid_.begin(); i != grid_.end(); i++ ) { i->resize( h ); }
	}
	void insert( const sf::Vector2f& p )
	{
		const sf::Vector2f g = imageToGrid( p, cellSize_ );
		grid_[ g.x ][ g.y ] = p;
	}
	bool isInNeighbourhood( const sf::Vector2f& point, float minDist, float cellSize )
	{
		const sf::Vector2f g = imageToGrid( point, cellSize );

		// number of adjucent cells to look for neighbour points
		const int D = 5;

		// scan the neighbourhood of the point in the grid
		for ( int i = g.x - D; i <= g.x + D; i++ )
		{
			for ( int j = g.y - D; j <= g.y + D; j++ )
			{
				if ( i >= 0 && i < w_ && j >= 0 && j < h_ )
				{
					const sf::Vector2f P = grid_[ i ][ j ];

					if ( getDistance( P, point ) < minDist )
						return true;
				}
			}
		}

		return false;
	}

private:
	int w_;
	int h_;
	float cellSize_;
	std::vector< std::vector<sf::Vector2f> > grid_;
};


void generatePoints(std::vector<sf::Vector2f> &points, int amountToSpawn, float minDist, float YtoX)
{
	std::random_device generator;

	std::uniform_real_distribution<> randx(0.0, 1.0);
	std::uniform_real_distribution<> randy(0.0, YtoX);
	// if minimum distance is not specified we simply return a list of random points
	if(minDist == 0)
	{
		while(amountToSpawn--)
		{
			points.push_back({randx(generator),randy(generator)});
		}

		return;
	}

	// otherwise we use Poisson Disk Sampling
	const float cellSize = minDist / sqrt(2);

	const int gridW = ( int )ceil( 1.0f / cellSize );
	const int gridH = ( int )ceil( YtoX / cellSize );

	std::vector<sf::Vector2f> processList;
	Grid grid( gridW, gridH, cellSize );

	sf::Vector2f firstPoint = {randx(generator),randy(generator)};

	processList.push_back( firstPoint );
	points.push_back( firstPoint );
	grid.insert( firstPoint );

	int k = 30;


	while(!processList.empty() && points.size() <= amountToSpawn)
	{
		const sf::Vector2f point = popRandom(processList);

		for( int i = 0; i < k; i++ )
		{
			const sf::Vector2f newPoint = generateRandomPointAround( point, minDist);

			//std::cout << "New Point: (" << newPoint.x << ", " << newPoint.y << ")\n";
			const bool canFitPoint = isInRectangle(newPoint, YtoX);

			if( canFitPoint && !grid.isInNeighbourhood(newPoint ,minDist, cellSize ) )
			{
				processList.push_back(newPoint);
				points.push_back(newPoint);
				grid.insert(newPoint);
				continue;
			}
		}
	}
	while (points.size() > amountToSpawn)
	{
		popRandom(points);
	}
	
}