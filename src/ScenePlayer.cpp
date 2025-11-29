#include <ScenePlayer.h>

#define BASE_SPEED 100
#define DURATION 0.1

double x = 100;
double dir = BASE_SPEED;
double counter = 0;

void ScenePlayer::walkRight() {
    m_Cow->SetTexture(m_Walking, 128, 128, DURATION, 4, 7);
    m_Cow->Play();
    dir = BASE_SPEED;
    counter = 0;
}

void ScenePlayer::standStill() {
    m_Cow->SetTexture(m_Walking, 128, 128, 0.25, 10, 10);
    m_Cow->Play();
    dir = 0;
    counter = 0.5;
}

void ScenePlayer::walkLeft() {
    m_Cow->SetTexture(m_Walking, 128, 128, DURATION, 0, 3);
    m_Cow->Play();
    dir = -BASE_SPEED;
    counter = 0;
}

ScenePlayer::ScenePlayer()
{
    m_Background = std::make_unique<Background>();
    m_Camera = std::make_shared<Camera>(0);
    m_Cow = std::make_unique<Animation>();
}

ScenePlayer::~ScenePlayer()
{
}

void ScenePlayer::SetBackgroundTexture(std::shared_ptr<SDL_Texture> bg)
{
    m_Background->SetTexture(bg);
}

void ScenePlayer::CheatInit(std::shared_ptr<SDL_Renderer> renderer)
{
    m_Walking = HelperFunctions::LoadTexture(renderer, "images/cow/cow_walk.png");
    walkRight();
}

void ScenePlayer::Draw(std::shared_ptr<SDL_Renderer> renderer)
{
    m_Background->Draw(renderer, m_Camera);
    m_Cow->Draw(renderer, m_Camera, x, 150, 128, 128);
}

void ScenePlayer::Update(double deltaTime)
{
    x += deltaTime * dir;
    counter -= deltaTime;

    if (x > m_Camera->getX() + 250)
        m_Camera->setX(x - 250);
    else if (x <= m_Camera->getX() + 50)
        m_Camera->setX(x - 50);

    if (x > 650) {
        if (dir > 0)
            standStill();
        else if (dir == 0 && counter <= 0)
            walkLeft();
    }

    if (x < -250) {
        if (dir < 0)
            standStill();
        else if (dir == 0 && counter <= 0)
            walkRight();
    }

    m_Cow->Update(deltaTime);
}
