#include "../include/GuiLite.h"
#include "wave_ctrl_ex.h"
#include <string.h>
#include <stdio.h>

#define	GRID_UNIT	16	//pixel
#define GRID_COLOR	GL_RGB(0, 80, 0)

void c_ecg_wave_ctrl::on_paint()
{
	draw_grid();

	c_rect rect;
	get_screen_rect(rect);
	//show name
	c_word::draw_string(m_surface, m_z_order, m_wave_name, m_wave_left + 10, rect.m_top, m_wave_name_font, m_wave_name_color, GL_ARGB(0, 0, 0, 0));
	//show unit
	c_word::draw_string(m_surface, m_z_order, m_wave_unit, m_wave_left + 60, rect.m_top, m_wave_unit_font, m_wave_unit_color, GL_ARGB(0, 0, 0, 0));
	//show gain
	c_word::draw_string(m_surface, m_z_order, "X1", m_wave_left + 70 , rect.m_top, c_theme::get_font(FONT_DEFAULT), m_wave_color, GL_ARGB(0, 0, 0, 0));

	//show scale rule
	int base_line = (m_wave_top + m_wave_bottom) / 2;
	int ruler_Height = 17;
	m_surface->draw_vline(rect.m_left + 74, base_line-ruler_Height, base_line+ruler_Height, m_wave_color, m_z_order);
	m_surface->draw_vline(rect.m_left + 75, base_line-ruler_Height, base_line+ruler_Height, m_wave_color, m_z_order);
	m_surface->draw_vline(rect.m_left + 76, base_line-ruler_Height, base_line+ruler_Height, m_wave_color, m_z_order);

	//show scale value
	c_rect mvRect;
	mvRect.m_left = rect.m_left + 78;
	mvRect.m_top = base_line + 5;
	mvRect.m_right = mvRect.m_left + 100;
	mvRect.m_bottom = mvRect.m_top + 30;

	//show unit
	c_word::draw_string_in_rect(m_surface, m_z_order, "1mv", mvRect, m_wave_unit_font, m_wave_color, GL_ARGB(0, 0, 0, 0));

	save_background();
}

void c_ecg_wave_ctrl::draw_grid()
{
	c_rect rect;
	get_screen_rect(rect);
	
	int row_cnt = rect.height() / GRID_UNIT;
	int col_cnt = rect.width() / GRID_UNIT;

	int left = rect.m_left + 2 * GRID_UNIT;
	int right = (rect.m_left + (col_cnt - 1) * GRID_UNIT);
	for (int y = 0; y < row_cnt; ++y)
	{
		m_surface->draw_hline(left, right, (rect.m_top + y * GRID_UNIT), GRID_COLOR, m_z_order);
	}

	int top = rect.m_top;
	int bottom = (rect.m_top + (row_cnt - 1) * GRID_UNIT);
	for (int x = 2; x < col_cnt; ++x)
	{
		m_surface->draw_vline((rect.m_left + x * GRID_UNIT), top, bottom, GRID_COLOR, m_z_order);
	}
}

/////////////////////////////////////////////////////////////

void c_bitmap_wave_ctrl::on_paint()
{
	c_rect rect;
	get_screen_rect(rect);

	m_surface->fill_rect(rect.m_left, rect.m_top, rect.m_right, rect.m_bottom, m_back_color, m_z_order);
	c_bitmap::draw_bitmap(m_surface, m_z_order, c_theme::get_bmp(m_bitmap_type), rect.m_left, rect.m_top);

	//show name
	c_word::draw_string(m_surface, m_z_order, m_wave_name, m_wave_left + 10, rect.m_top, m_wave_name_font, m_wave_name_color, GL_ARGB(0, 0, 0, 0), ALIGN_LEFT);
	//show unit
	c_word::draw_string(m_surface, m_z_order, m_wave_unit, m_wave_left + 60, rect.m_top, m_wave_unit_font, m_wave_unit_color, GL_ARGB(0, 0, 0, 0), ALIGN_LEFT);

	save_background();
}