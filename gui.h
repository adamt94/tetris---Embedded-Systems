/******************************************************************************/
/* This file has been generated by the uGFX-Studio                            */
/*                                                                            */
/* http://ugfx.org                                                            */
/******************************************************************************/

#ifndef _GUI_H_
#define _GUI_H_

#include "gfx.h"

// GListeners
extern GListener gl;

// GHandles
extern GHandle ghContainerPage0;
extern GHandle ghContainer1;
extern GHandle ghLabel1;
extern GHandle ghButton1;
extern GHandle ghButton2;

// Function Prototypes
void guiCreate(void);
void guiShowPage(unsigned pageIndex);
void guiEventLoop(void);

#endif /* _GUI_H_ */
