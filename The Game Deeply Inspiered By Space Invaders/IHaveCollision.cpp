#include "IHaveCollision.h"

//bool IHaveCollision::IsColliding(sf::FloatRect other) {
//	sf::Vector2f other_top_left = other.position;
//	sf::Vector2f other_bottom_right = other.position + other.size;
//	sf::Vector2f collider_top_left = collider.position;
//	sf::Vector2f collider_bottom_right = collider.position + collider.size;
//	
//	return (other_bottom_right.x >= collider_top_left.x) && (other_bottom_right.y >= collider_top_left.y) && (other_top_left.x <= collider_top_left.x) && (other_top_left.y <= collider_top_left.y);
//}
bool IHaveCollision::IsColliding(sf::FloatRect other) {
	bool top_left = other.contains(collider.position);
	bool top_right = other.contains(sf::Vector2f(collider.position.x + collider.size.x, collider.position.y));
	bool bottom_left = other.contains(sf::Vector2f(collider.position.x, collider.position.y + collider.size.y));
	bool bottom_right = other.contains(collider.position + collider.size);
	
	return top_left || top_right || bottom_left || bottom_right;
}

void IHaveCollision::SetCollider(sf::Vector2f pos, sf::Vector2f size) { collider = sf::FloatRect(pos, size); }
sf::FloatRect IHaveCollision::GetCollider() { return collider; }
