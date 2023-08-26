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

#ifndef HEADER_SUPERTUX_BADGUY_CRYSTAL_HAYWIRE_HPP
#define HEADER_SUPERTUX_BADGUY_CRYSTAL_HAYWIRE_HPP

#include "badguy/haywire.hpp"

class CrystalHaywire final : public Haywire
{
public:
  CrystalHaywire(const ReaderMapping& reader);

  virtual void kill_fall() override;

  static std::string class_name() { return "crystal-haywire"; }
  virtual std::string get_class_name() const override { return class_name(); }
  static std::string display_name() { return _("Crystal Haywire"); }
  virtual std::string get_display_name() const override { return display_name(); }
  virtual std::string get_overlay_size() const override { return "1x1"; }

  virtual void active_update(float dt_sec) override;

private:
  CrystalHaywire(const CrystalHaywire&) = delete;
  CrystalHaywire& operator=(const CrystalHaywire&) = delete;
};

#endif

/* EOF */
