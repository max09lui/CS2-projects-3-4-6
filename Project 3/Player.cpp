#include <iostream>
#include "Player.h"
#include "Arena.h"
#include "Globals.h"

using namespace std;

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "The player must be in some Arena!" << endl;
        exit(1);
    }
    if (r < 1 || r > ap->rows() || c < 1 || c > ap->cols())
    {
        cout << "Player created with invalid coordinates (" << r
            << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}
int Player::age() const
{
    return m_age;
}
string Player::takeComputerChosenTurn()
{

    if (m_arena->nRobotsAt(m_row, m_col + 1) + m_arena->nRobotsAt(m_row, m_col - 1) + m_arena->nRobotsAt(m_row + 1, m_col) + m_arena->nRobotsAt(m_row - 1, m_col) > 0)
    {
        if (m_arena->nRobotsAt(m_row + 1, m_col) == 0 && m_row + 1 > 0 && m_row + 1 <= m_arena->rows())
        {
            move(DOWN);
            return "Moved.";
        }
        else if (m_arena->nRobotsAt(m_row - 1, m_col) == 0 && m_row - 1 > 0 && m_row - 1 <= m_arena->rows())
        {
            move(UP);
            return "Moved.";
        }
        else if (m_arena->nRobotsAt(m_row, m_col + 1) == 0 && m_col + 1 > 0 && m_col + 1 <= m_arena->rows())
        {
            move(RIGHT);
            return "Moved.";
        }
        else if (m_arena->nRobotsAt(m_row, m_col - 1) == 0 && m_col - 1 > 0 && m_col - 1 <= m_arena->rows())
        {
            move(LEFT);
            return "Moved.";
        }
    }
    //no robots endangering player 

    for (int i = 1; i <= MAXSHOTLEN; i++)
    {
        if(m_arena->nRobotsAt(m_row, m_col + i) > 0)
        {
            bool status = shoot(RIGHT);
            if (status == true)
            {
                return "Shot and hit!";
            }
            else
            {
                return "Shot and missed!";
            }
        }
        if (m_arena->nRobotsAt(m_row, m_col - i) > 0)
        {
            bool status = shoot(LEFT);
            if (status)
            {
                return "Shot and hit!";
            }
            else
            {
                return "Shot and missed!";
            }
        }
        if (m_arena->nRobotsAt(m_row + i, m_col) > 0)
        {
            bool status = shoot(DOWN);
            if (status == true)
            {
                return "Shot and hit!";
            }
            else
            {
                return "Shot and missed!";
            }
        }
        if (m_arena->nRobotsAt(m_row - i, m_col) > 0)
        {
            bool status = shoot(UP);
            if (status == true)
            {
                return "Shot and hit!";
            }
            else
            {
                return "Shot and missed!";
            }
        }
    }


    stand();
    return "Stood.";
}

void Player::stand()
{
    m_age++;
}

void Player::move(int dir)
{
    m_age++;
    switch (dir)
    {
    case UP:
        if (m_row - 1 > 0 && m_row - 1 <= m_arena->rows())
        {
            m_row--;
        }
        break;
    case DOWN:
        if (m_row + 1 > 0 && m_row + 1 <= m_arena->rows())
        {
            m_row++;
        }
        break;
    case LEFT:
        if (m_col - 1 > 0 && m_col - 1 <= m_arena->cols())
        {
            m_col--;
        }
        break;

    case RIGHT:
        if (m_col + 1 > 0 && m_col + 1 <= m_arena->cols())
        {
            m_col++;
        }
        break;
    }
    
}

bool Player::shoot(int dir)
{
    m_age++;
    int a = rand() % 3;
    if (a == 0)  // miss with 1/3 probability
    {
        return false;
    }
    switch (dir)
    {
    case UP:
        for (int i = 1; i <= MAXSHOTLEN; i++)
        {
            if (m_arena->nRobotsAt(m_row - i, m_col) > 0)
            {
                m_arena->damageRobotAt(m_row - i, m_col);
                return true;
            }
        }
    case DOWN:
        for (int i = 1; i <= MAXSHOTLEN; i++)
        {
            if (m_arena->nRobotsAt(m_row + i, m_col) > 0)
            {
                m_arena->damageRobotAt(m_row + i, m_col);
                return true;
            }
        }
    case LEFT:
        for (int i = 1; i <= MAXSHOTLEN; i++)
        {
            if (m_arena->nRobotsAt(m_row, m_col - i) > 0)
            {
                m_arena->damageRobotAt(m_row, m_col - i);
                return true;
            }
        }
    case RIGHT:
        for (int i = 1; i <= MAXSHOTLEN; i++)
        {
            if (m_arena->nRobotsAt(m_row, m_col + i) > 0)
            {
                m_arena->damageRobotAt(m_row, m_col + i);
                return true;
            }
        }
    }

    return false;  // nothing in range therefore miss 
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

