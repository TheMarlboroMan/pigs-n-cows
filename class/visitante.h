#ifndef VISITANTE_H
#define VISITANTE_H

class Actor;
class Cerdito;
class Vaquita;
class Cerdito_tierra;
class Vaquita_tierra;
class Arco_iris;
class Nube;
class Bonus;

class Visitante
{
	public:

	Visitante(){}

	virtual void visitar(const Actor&) {}
	virtual void visitar(const Cerdito&)=0;
	virtual void visitar(const Vaquita&)=0;
	virtual void visitar(const Cerdito_tierra&)=0;
	virtual void visitar(const Vaquita_tierra&)=0;
	virtual void visitar(const Arco_iris&)=0;
	virtual void visitar(const Nube&)=0;
	virtual void visitar(const Bonus&)=0;
};

#endif
