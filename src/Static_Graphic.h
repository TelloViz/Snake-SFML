#pragma once
#include <string>
#include <SFML/Graphics.hpp>


class Static_Graphic : public sf::Drawable
{
public:
	Static_Graphic(const std::string& fp);
	Static_Graphic(const std::string& fp, sf::Vector2f size);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setPosition(sf::Vector2f pos);
	void scale(sf::Vector2f scale);
	void rotate(float angle);

private: // private methods
	void initializeTexture();
	void applyTextureToSprite();

private: // private data
	std::string m_fp;
	sf::Texture m_texture;
	sf::Sprite  m_sprite;

};

