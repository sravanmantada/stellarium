/*
 * Stellarium
 * Copyright (C) 2002 Fabien Chereau
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef _CONSTELLATION_H_
#define _CONSTELLATION_H_

#include "hip_star_mgr.h"
#include "stellarium.h"
#include "stel_utility.h"
#include "s_font.h"
#include "fader.h"
#include <vector>

class Constellation
{
    friend class ConstellationMgr;
public:
    Constellation();
    ~Constellation();
    bool read(const string& record, HipStarMgr * _VouteCeleste);
//    void draw(Projector* prj) const;
    void draw_name(s_font * constfont, Projector* prj) const;
    void draw_art(Projector* prj, Navigator* nav) const;
    void draw_boundary_optim(Projector* prj) const;
    const Constellation* is_star_in(const HipStar *) const;
    string getNameI18(void) { return nameI18; };
    string getShortName(void) { return abbreviation; };
    static void  set_line_color(const Vec3f& c) { line_color = c; }
    static Vec3f get_line_color() { return line_color; }

    static void  set_label_color(const Vec3f& c) { label_color = c; }
    static Vec3f get_label_color() { return label_color; }

    static void  set_boundary_color(const Vec3f& c) { boundary_color = c; }
    static Vec3f get_boundary_color() { return boundary_color; }
private:
    void draw_optim(Projector* prj) const;
    void draw_art_optim(Projector* prj, Navigator* nav) const;
	void update(int delta_time);
	void set_flag_lines(bool b) {line_fader=b;}
	void set_flag_boundaries(bool b) {boundary_fader=b;}
	void set_flag_name(bool b) {name_fader=b;}
	void set_flag_art(bool b) {art_fader=b;}
	bool get_flag_lines(void) {return line_fader;}
	bool get_flag_boundaries(void) {return boundary_fader;}
	bool get_flag_name(void) {return name_fader;}
	bool get_flag_art(void) {return art_fader;}
	
	//! International name (translated using gettext)
    string nameI18;
    //! Name in english
	string englishName;
	//! Abbreviation of the latin name (for western constellations)
    string abbreviation;
    Vec3f XYZname;
	Vec3d XYname;
    unsigned int nb_segments;
    HipStar ** asterism;
	static bool gravity_label;
	s_texture* art_tex;
	Vec3d art_vertex[9];
	LinearFader art_fader, line_fader, name_fader, boundary_fader;
	static Vec3f line_color, label_color, boundary_color;

	static bool singleSelected;
	vector<vector<Vec3f> *> isolatedBoundarySegments;
	vector<vector<Vec3f> *> sharedBoundarySegments;
};

#endif // _CONSTELLATION_H_
