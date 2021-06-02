#ifndef CAJA_MOTOR_H
#define CAJA_MOTOR_H

#include "../herramientas/herramientas.h"
#include "../punto_2d/punto_2d.h"

namespace DLibH
{
/*Una caja para no estar siempre comprometidos con la representación SDL de 
la misma. Incluye además algunos métodos típicos de colisión y cosas así.*/

template<typename T, typename U>
class Caja
{
	public:
	Punto_2d<T> origen;
	U w;
	U h;

	Caja(const Punto_2d<T>& p, U pw, U ph)
		:origen(p), w(pw), h(ph)
	{}

	Caja(T px, T py, U pw, U ph)
		:origen(px, py), w(pw), h(ph)
	{}

	Caja(const Caja& c)
		:origen(c.origen), w(c.w), h(c.h)
	{}

	Caja& operator=(const Caja& c)
	{
		origen=c.origen;
		w=c.w;
		h=c.h;
		return *this;
	}

	bool es_en_colision_con(const Caja& c, bool roce_es_colision=false) const {return cajas_superpuestas(*this, c, roce_es_colision);}
	bool es_en_colision_con(const Caja& c, Caja& r, bool roce_es_colision=false) const {return cajas_superpuestas(*this, c, r, roce_es_colision);}
	bool es_punto_dentro(const Punto_2d<T>& p) const {return punto_dentro_de_caja(p.x, p.y);}
	bool es_punto_dentro(T x, T y) const {return punto_dentro_de_caja(*this, x, y);}
	bool es_contenida_en(const Caja& gran) const {return caja_dentro_de_caja(*this, gran);}
	bool es_contiene_a(const Caja& peq) const {return caja_dentro_de_caja(peq, *this);}
	static bool cajas_superpuestas(const Caja& c1, const Caja& c2, bool roce_es_colision=false){return Herramientas::rectangulos_superpuestos(c1.origen.x, c1.origen.y, c1.w, c1.h, c2.origen.x, c2.origen.y, c2.w, c2.h, roce_es_colision);}
	static bool cajas_superpuestas(const Caja& c1, const Caja& c2, Caja& cr, bool roce_es_colision=false){return Herramientas::rectangulos_superpuestos(c1.origen.x, c1.origen.y, c1.w, c1.h, c2.origen.x, c2.origen.y, c2.w, c2.h, cr.origen.x, cr.origen.y, cr.w, cr.h, roce_es_colision);}
	static bool caja_dentro_de_caja(const Caja& peq, const Caja& gran){return Herramientas::caja_en_caja(peq.origen.x, peq.origen.y, peq.w, peq.h, gran.origen.x, gran.origen.y, gran.w, gran.h);}
	static bool punto_dentro_de_caja(const Caja& c, const Punto_2d<T> p){return punto_dentro_de_caja(c, p.x, p.y);}
	static bool punto_dentro_de_caja(const Caja& c, T x, T y){return Herramientas::punto_en_caja(c.origen.x, c.origen.y, c.w, c.h, x, y);}
	
};

}
#endif
