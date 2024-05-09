//
// ScatteredMosaicBrush.cpp
//
// Implementation of a scattered mosaic brush with random rotations and transparency.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredMosaicBrush.h"

#include <cstdlib>
#include <cmath>

ScatteredMosaicBrush::ScatteredMosaicBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredMosaicBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	BrushMove(source, target);
}

void ScatteredMosaicBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredMosaicBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int density = 10;  // You can adjust this value to change the number of rectangles scattered

	glBegin(GL_QUADS);
	for (int i = 0; i < density; ++i) {
		// Randomize the positions within the brush size
		float offsetX = static_cast<float>(rand() % size - size / 2);
		float offsetY = static_cast<float>(rand() % size - size / 2);

		// Calculate the center of the rectangle
		float centerX = target.x + offsetX;
		float centerY = target.y + offsetY;

		// Random size and rotation
		float rectSize = static_cast<float>(rand() % (size / 2) + 1);
		float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.0f; // Convert to radians

		// Set color with random alpha for transparency
		SetColor(source);

		// Compute rotated rectangle corners
		float cosTheta = cos(angle);
		float sinTheta = sin(angle);
		float halfSize = rectSize / 2;

		float x1 = centerX + (-halfSize * cosTheta - -halfSize * sinTheta);
		float y1 = centerY + (-halfSize * sinTheta + -halfSize * cosTheta);
		float x2 = centerX + (halfSize * cosTheta - -halfSize * sinTheta);
		float y2 = centerY + (halfSize * sinTheta + -halfSize * cosTheta);
		float x3 = centerX + (halfSize * cosTheta - halfSize * sinTheta);
		float y3 = centerY + (halfSize * sinTheta + halfSize * cosTheta);
		float x4 = centerX + (-halfSize * cosTheta - halfSize * sinTheta);
		float y4 = centerY + (-halfSize * sinTheta + halfSize * cosTheta);

		// Draw rotated rectangle
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
		glVertex2f(x4, y4);
	}
	glEnd();
}

void ScatteredMosaicBrush::BrushEnd(const Point source, const Point target)
{
	// Nothing to clean up specifically
	glDisable(GL_BLEND);
}
