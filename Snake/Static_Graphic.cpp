#include "Static_Graphic.h"

Static_Graphic::Static_Graphic(const std::string& fp)
	: m_fp{fp}
{
	initializeTexture();
	applyTextureToSprite();
}

Static_Graphic::Static_Graphic(const std::string& fp, sf::Vector2f size)
	: m_fp{ fp }
{
}

void Static_Graphic::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite);
}

void Static_Graphic::setPosition(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}

void Static_Graphic::scale(sf::Vector2f fac)
{
	m_sprite.scale(fac);
}

void Static_Graphic::rotate(float angle)
{
	m_sprite.setRotation(angle);
}

void Static_Graphic::initializeTexture()
{
	m_texture.loadFromFile(m_fp);
}

void Static_Graphic::applyTextureToSprite()
{	
	m_sprite.setTexture(m_texture);
}
