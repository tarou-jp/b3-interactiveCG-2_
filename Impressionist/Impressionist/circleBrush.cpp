//
// pointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "circleBrush.h"
#include <math.h>
#define PI 3.1415

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize((float)size);

	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	//�X���C�_�[��������

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove  document is NULL\n");
		return;
	}

    //�_�C�A���O�̃X���C�_�[����u���V�̑傫�����擾
	int size = pDoc->getSize();
	int div = 12;
	float radius = size / 2.0;
	float Ax, Ay;

	//������GL_POLYGON�̏ꍇ�A�ʑ��p�`��`��
	glBegin(GL_POLYGON);
	SetColor( source );
	for (int i = 0; i < div; i++) {
		Ax = target.x + radius * cos(2 * PI * i / div);
		Ay = target.y + radius * sin(2 * PI * i / div);
		glVertex2f(Ax, Ay);
	}
	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
	glDisable(GL_BLEND);

}

