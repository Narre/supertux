//  SuperTux
//  Copyright (C) 2023 Jiri Palecek <narre@protonmail.com>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "badguy/crystal_haywire.hpp"
#include "object/explosion.hpp"
#include "object/player.hpp"
#include "object/shard.hpp"
#include "supertux/sector.hpp"

const float TRIGGER_DISTANCE = 320.f;
const float TRIGGERED_TIME = 0.8f;

CrystalHaywire::CrystalHaywire(const ReaderMapping& reader) :
  Haywire(reader, "images/creatures/crystal_haywire/crystal_haywire.sprite")
{
}

void
CrystalHaywire::kill_fall()
{
  if (is_exploding) {
    ticking->stop();
    grunting->stop();
  }
  if (is_valid()) {
    if (m_frozen)
      BadGuy::kill_fall();
    else
    {
      remove_me();
      Sector::get().add<Explosion>(m_col.m_bbox.get_middle(), EXPLOSION_STRENGTH_DEFAULT);
      Sector::get().add<Shard>(m_col.m_bbox.get_middle(), Vector(100.f, -500.f));
      Sector::get().add<Shard>(m_col.m_bbox.get_middle(), Vector(270.f, -350.f));
      Sector::get().add<Shard>(m_col.m_bbox.get_middle(), Vector(-100.f, -500.f));
      Sector::get().add<Shard>(m_col.m_bbox.get_middle(), Vector(-270.f, -350.f));
      run_dead_script();
    }
  }
}

void
CrystalHaywire::active_update(float dt_sec)
{
  if (!is_exploding && !m_frozen)
  {
    std::vector<MovingObject*> objects = Sector::get().get_nearby_objects(get_bbox().get_middle(), TRIGGER_DISTANCE);
    for (MovingObject* object : objects)
    {
      auto player = dynamic_cast<Player*>(object);
      if(player && !player->get_ghost_mode())
      {
        if (!((m_dir == Direction::LEFT &&
            Sector::get().can_see_player(Vector(get_bbox().get_left() - 1.f,
                                                get_bbox().get_middle().y)))
            || (m_dir == Direction::RIGHT &&
            Sector::get().can_see_player(Vector(get_bbox().get_right() + 1.f,
                                                get_bbox().get_middle().y)))
           )) continue;

        m_physic.set_velocity_x(0.f);
        start_exploding();
        stomped_timer.start(TRIGGERED_TIME);
      }
    }
  }

  Haywire::active_update(dt_sec);
}
/* EOF */
