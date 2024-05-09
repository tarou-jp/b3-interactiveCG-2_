#pragma once
#pragma once
//
// ExplosionBrush.h
//
// Header file for Explosion Brush.
//

#ifndef EXPLOSIONBRUSH_H
#define EXPLOSIONBRUSH_H

#include "impBrush.h"

class ExplosionBrush : public ImpBrush
{
public:
	ExplosionBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif
