using namespace DLibH;

template<typename T, typename U> bool Herramientas::rectangulos_superpuestos(T x1, T y1, U w1, U h1, T x2, T y2, U w2, U h2, bool roce_es_colision)
//template<typename T> bool Herramientas::rectangulos_superpuestos(T x1, T y1, T w1, T h1, T x2, T y2, T w2, T h2, bool roce_es_colision)
{
        bool dentro_x;
        bool dentro_y;

	T x2_w2=(x2+w2);
	T x1_w1=(x1+w1);
	T y2_h2=(y2+h2);
	T y1_h1=(y1+h1);

        //Comparamos si está fuera y lo negamos...
	/* Comprobación empírica...

0	     10           
|---- A ------|---- B ----|
	     10          20

		Si el roce es colisión:
			dentro_x=!( (x2_w2 < x1) || (x2 > x1_w1) );
			dentro_x=!( (20 < 0) || (10 > 10) );
			dentro_x=!( false || false );
			dentro_x=!(false)
			dentro_x=true

		Si el roce no es colisión...

			dentro_x=!( (x2_w2 <= x1) || (x2 >= x1_w1) );
			dentro_x=!( (20 <= 0) || (10 >= 10) );
			dentro_x=!( false || true );
			dentro_x=!(true)
			dentro_x=false
	*/
	
        if(roce_es_colision)
        {
		dentro_x=!( (x2_w2 < x1) || (x2 > x1_w1) );
		dentro_y=!( (y2_h2 < y1) || (y2 > y1_h1) );
        }
        else
        {
		dentro_x=!( (x2_w2 <= x1) || (x2 >= x1_w1) );
		dentro_y=!( (y2_h2 <= y1) || (y2 >= y1_h1) );
        }

        return dentro_x&&dentro_y;
}

template <typename T, typename U> bool Herramientas::rectangulos_superpuestos(
	T x1, T y1, U w1, U h1, 
	T x2, T y2, U w2, U h2, 
	T& rx, T& ry, U& rw, U& rh, 
	bool roce_es_colision)
{
	if(!rectangulos_superpuestos(x1, y1, w1, h1, x2, y2, h2, h2, roce_es_colision))
	{
		return false;
	}
	else
	{
		//Esta caja es la que ambos tienen en común...

		T x1_w1=x1+w1;
		T x2_w2=x2+w2;
		T y1_h1=y1+h1;
		T y2_h2=y2+h2;

		posicion_dimension_segmentos(x1, x1_w1, x2, x2_w2, rx, rw);
		posicion_dimension_segmentos(y1, y1_h1, y2, y2_h2, ry, rh);

		//Cuando hay dimensiones muy pequeñas esto puede importar.
		if(!roce_es_colision)
		{
			if(rw) rw++;
			if(rh) rh++;
		}		

		return true;
	}
}

/*
Suponiendo dos segmentos que se superponen se puede sacar el inicio y el fin de
dicha superposición.
En el archivo tests_ejemplos/test_01.cpp tenemos un ejemplillo de todo esto
y las explicaciones pertintentes...
*/

template <typename T, typename U> void Herramientas::posicion_dimension_segmentos(T aini, T afin, T bini, T bfin, T &resultado_pos, U &resultado_dim)
//template <typename T> void Herramientas::posicion_dimension_segmentos(T aini, T afin, T bini, T bfin, T &resultado_pos, T &resultado_dim)
{
	bool c1=aini < bini;
	bool c2=afin < bfin;
	bool c3=bini < aini;
	bool c4=bfin < afin;
	bool c5=aini == bini;
	bool c6=afin == bfin;
	
	//Idénticos...
	if(c5 && c6)
	{
		posicion_dimension_segmentos_solucion_completa(bini, bfin, aini, afin, resultado_pos, resultado_dim);
	}
	//A a la izquierda de B
	else if(c1 && c2) 
	{
		posicion_dimension_segmentos_solucion_parcial(aini, afin, bini, bfin, resultado_pos, resultado_dim); //Caso 1
	}
	//B a la izquierda de A
	else if(c3 && c4) 
	{
		posicion_dimension_segmentos_solucion_parcial(bini, bfin, aini, afin, resultado_pos, resultado_dim); //Caso 2
	}
	//A dentro de B
	else if(!c1 && !c4) 
	{
		posicion_dimension_segmentos_solucion_completa(aini, afin, bini, bfin, resultado_pos, resultado_dim); //Caso 3
	}
	//B dentro de A
	else if(!c2 && !c3) 
	{
		posicion_dimension_segmentos_solucion_completa(bini, bfin, aini, afin, resultado_pos, resultado_dim); //Caso 4
	}
}

/*
Un segmento está parcialmente dentro de otro, como en este ejemplo:

	|------ SEGMENTO A ---------|
			     XXXXXXXX
			     |-------- SEGMENTO B ------|
*/

template <typename T, typename U> void Herramientas::posicion_dimension_segmentos_solucion_parcial(T aini, T afin, T bini, T bfin, T &resultado_pos, U &resultado_dim)
//template <typename T> void Herramientas::posicion_dimension_segmentos_solucion_parcial(T aini, T afin, T bini, T bfin, T &resultado_pos, T &resultado_dim)
{
	resultado_pos=bini;
	resultado_dim=afin-bini;
}

/*Un segmento está completamente dentro de otro....

		|--- SEGMENTO A ----|
	|-------XXXX SEGMENTO B XXXXX ---|
*/

template <typename T, typename U> void Herramientas::posicion_dimension_segmentos_solucion_completa(T aini, T afin, T bini, T bfin, T &resultado_pos, U &resultado_dim)
//template <typename T> void Herramientas::posicion_dimension_segmentos_solucion_completa(T aini, T afin, T bini, T bfin, T &resultado_pos, T &resultado_dim)
{
	resultado_pos=aini;
	resultado_dim=afin-aini;
}

