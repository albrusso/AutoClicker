/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 14:17:46 by albrusso          #+#    #+#             */
/*   Updated: 2024/04/22 10:16:08 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

void click(int x, int y)
{
    CGEventRef click_down = CGEventCreateMouseEvent
    (
        NULL, kCGEventLeftMouseDown,
        CGPointMake(x, y),
        kCGMouseButtonLeft
    );
    CGEventRef click_up = CGEventCreateMouseEvent
    (
        NULL, kCGEventLeftMouseUp,
        CGPointMake(x, y),
        kCGMouseButtonLeft
    );
    CGEventPost(kCGHIDEventTap, click_down);
    usleep(10000);
    CGEventPost(kCGHIDEventTap, click_up);
    CFRelease(click_down);
    CFRelease(click_up);
}

int main(void)
{
    int num_clicks;
    printf("how many clicks do you want to make? (0 for an infinite loop): ");
    scanf("%d", &num_clicks);
    int infinite = (num_clicks == 0);
    if (infinite)
        printf("The program is in infinite loop mode. Press ctrl+c to stop.\n");
 	printf("The program will start in 10 seconds.\n");
    for (int i = 10; i > 0; i--) 
    {
        printf("%d...\n", i);
        sleep(1);
    }
    while (infinite || num_clicks > 0)
    {
        CGEventRef event = CGEventCreate(NULL);
        CGPoint loc = CGEventGetLocation(event);
        CFRelease(event);
        int x = loc.x;
        int y = loc.y;
        click(x, y);
        usleep(250000);
        if (!infinite)
            num_clicks--;
    }
    return 0;
}
