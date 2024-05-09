//
// ExplosionBrush.cpp
//
// Implementation of an explosion brush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ExplosionBrush.h"

#include <cstdlib>
#include <cmath>

ExplosionBrush::ExplosionBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ExplosionBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	BrushMove(source, target);
}

void ExplosionBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ExplosionBrush::BrushMove document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int numRays = 20;  // Adjust to control number of fragments
	float maxRayLength = static_cast<float>(size);

	// Draw explosion rays
	glBegin(GL_LINES);
	for (int i = 0; i < numRays; ++i) {
		float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.0f; // Convert to radians
		float length = static_cast<float>(rand() % static_cast<int>(maxRayLength));
		float endX = target.x + cos(angle) * length;
		float endY = target.y + sin(angle) * length;

		// Randomize color for each ray (e.g., yellow to red range)
		SetColor(source);

		glVertex2f(target.x, target.y);
		glVertex2f(endX, endY);
	}
	glEnd();

	// Draw explosion center as a collection of circles
	int numCircles = 15; // Adjust for different explosion effects
	glBegin(GL_TRIANGLE_FAN);
	for (int j = 0; j < numCircles; ++j) {
		float radius = static_cast<float>(rand() % size / 2);
		float angle = static_cast<float>(rand() % 360) * 3.14159f / 180.0f;

		// Adjust color, potentially adding varying transparency
		SetColor(source);

		glVertex2f(target.x + cos(angle) * radius, target.y + sin(angle) * radius);
	}
	glEnd();
}

void ExplosionBrush::BrushEnd(const Point source, const Point target)
{
	// Nothing to clean up specifically
	glDisable(GL_BLEND);
}
