#include "Collider.hpp"



// Adicione o trecho abaixo no começo do seu Collider.cpp,
// logo após os seus includes e antes de qualquer função.

#ifdef DEBUG
#include "Camera.hpp"
#include "Game.hpp"

#include <SDL2/SDL.h>
#endif // DEBUG





// Copie o conteúdo dessa função para dentro da sua e adapte o nome das funções para as suas.
// Funções usadas:
// Rect::GetCenter()				- Retorna um Vec2 no centro do Rect
// Vec2::operator-( const Vec2& )	- Subtrai dois Vec2
// Vec2::Rotate( float rad )		- Rotaciona um Vec2 pelo ângulo em radianos passado
void Collider::Render() {
#ifdef DEBUG
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).GetRotated( associated.angleDeg)
					+ center - associated.camera->pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y) - center).GetRotated( associated.angleDeg)
					+ center - associated.camera->pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated( associated.angleDeg)
					+ center - associated.camera->pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h) - center).GetRotated( associated.angleDeg)
					+ center - associated.camera->pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}


Collider::Collider (GameObject& associated, Vec2 scale, Vec2 offset) : Component(associated){
    this->scale = scale;
    this->offset = offset;
}

void Collider::Update(float dt){
    box.x = associated.box.x;
    box.y = associated.box.y;
    box.w = associated.box.w;
    box.h = associated.box.h;

    box.SetDims(Vec2(associated.box.w*scale.x, associated.box.h*scale.y));
    Vec2 off = offset.GetRotated(associated.angleDeg);
    box.x += off.x;
    box.y += off.y;
}

bool Collider::Is(std::string type){
    return !type.compare("Collider");
}

void Collider::SetScale(Vec2 scale){
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset){
    this->offset = offset;
}