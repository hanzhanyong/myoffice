#include "moElementFactory.h"
#include "moRoom.h"
#include "moRoomRect.h"
#include "moDoor.h"
#include "moVertex.h"
#include "moLine.h"

using namespace MyOffice;
using namespace MyOffice::DB;

static MoElementFactory *g_ElementFactory = NULL;

MoElementFactory::MoElementFactory()
{

}
MoElementFactory::~MoElementFactory()
{
	g_ElementFactory = NULL;
}

MoElementFactory *MoElementFactory::getInstance()
{
	if (g_ElementFactory == NULL)
		g_ElementFactory = new MoElementFactory();
	return g_ElementFactory;
}

MoElement *MoElementFactory::create(MoElementType type, int seqNo)
{
	MoElement *ele = NULL;
	switch (type)
	{
	case MET_ROOM:
		ele = new MoRoom();
		break;
	case MET_DOOR:
		ele = new MoDoor();
		break;
	case MET_VERTEX:
		ele = new MoVertex();
		break;
	case MET_LINE:
		ele = new MoLine();
		break;
	case MET_RECT:
		ele = new MoRoomRect();
		break;
	}
	if (ele)
		ele->setSeqNo(seqNo);
	return ele;
}