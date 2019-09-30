//Code inspired by Glenn Fowler's sudoku solver/generator
//The original is published under the following license
		/***********************************************************************
		*               This software is part of the ast package               *
		*          Copyright (c) 2005-2009 AT&T Intellectual Property          *
		*                      and is licensed under the                       *
		*                  Common Public License, Version 1.0                  *
		*                    by AT&T Intellectual Property                     *
		*                                                                      *
		*                A copy of the License is available at                 *
		*            http://www.opensource.org/licenses/cpl1.0.txt             *
		*         (with md5 checksum 059e8cd6165cb4c31e351f2b69388fd9)         *
		*                                                                      *
		*              Information and Software Systems Research               *
		*                            AT&T Research                             *
		*                           Florham Park NJ                            *
		*                                                                      *
		*                 Glenn Fowler <gsf@research.att.com>                  *
		***********************************************************************/
//This is a MODIFIED version of the original code

#ifndef SOLROWMINLEX_H_INCLUDED

#define SOLROWMINLEX_H_INCLUDED

#include <memory.h>
#include "t_128.h"
#include "fsss2.h"

#if defined(__GNUC__)
#define NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER) || defined(__INTEL_COMPILER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE
#endif

struct solRowMinLex
{
	struct transformationConstants
	{
		unsigned char	swap[18][9][9];
		unsigned char	perm[6][3];
		unsigned char	part[9][5];
		unsigned char	boxOffset[9];
	};
	static const solRowMinLex::transformationConstants tc;

	unsigned int	box;
	unsigned int	map[10];
	unsigned int	row[9];
	unsigned int	col[9];
	unsigned int	aut;
	solRowMinLex *next; //0 terminated chain of automorphic transformations for aut > 1

	void byGrid(const char* sol);
	//void byPuzzle(const char* sol);
	void transform(const char *in, char *out) const;
	void transform(const pencilmarks& in, pencilmarks& out) const;
	void reverseTransform(const char *in, char *out) const;
	//void toString(char *buf) const;
	solRowMinLex() : box(0), aut(0) {
		next = 0;
	}
	const solRowMinLex & operator=(const solRowMinLex &t) {
		memcpy((solRowMinLex*)this, &t, sizeof(solRowMinLex));
		if(t.next) {
			solRowMinLex *t = new solRowMinLex();
			*t = *next;
			next = t;
		}
		return *this;
	}
	~solRowMinLex() {
		if(next) {
			delete next;
		}
	}
	NOINLINE void addAutomorph(solRowMinLex *test) {
		solRowMinLex *t = new solRowMinLex();
		*t = *test;
		t->map[0] = 0;
		t->next = next; //???
		next = t;
	}
	NOINLINE void clearAutomorphs() {
		if(next) {
			next->clearAutomorphs();
			next = 0;
		}
	}
	bool isTransforming() const {
		if(aut != 1) return true;
		if(box) return true;
		for(unsigned int i = 0; i < 9; i++) {
			if(row[i] != i || col[i] != i || map[i] != i) return true;
		}
		if(map[9] != 9) return true;
		return false;
	}
	static void pmMinLex(const pencilmarks& src, const char* sol, pencilmarks& res);
};
#endif // SOLROWMINLEX_H_INCLUDED
