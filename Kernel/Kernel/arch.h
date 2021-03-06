//
//  arch.h
//  BetaOS
//
//  Created by Adam Kopeć on 12/10/15.
//  Copyright © 2015-2016 Adam Kopeć. All rights reserved.
//

#ifndef _KERNEL_ARCH_H
#define _KERNEL_ARCH_H

#include <stdbool.h>

void reboot_system(bool ispanic);
void shutdown_system(void);

#endif /* arch_h */
