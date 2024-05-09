#pragma once
//
// ScatteredMosaicBrush.h
//
// Header file for Scattered Mosaic Brush.
//

#ifndef SCATTEREDMOSAICBRUSH_H
#define SCATTEREDMOSAICBRUSH_H

#include "impBrush.h"

class ScatteredMosaicBrush : public ImpBrush
{
public:
	ScatteredMosaicBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void) { return "Scattered Mosaic Brush"; }
};

#endif
