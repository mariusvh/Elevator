/**
* @file
* @brief Queue operations
*/

#ifndef QUEUE_H
#define QUEUE_H

void reset_queue_matrix();

void update_queue_matrix();

int queue_anyOrders();

int queue_ordersAbove(Elevator e);

int queue_ordersUnder(Elevator e);

void queue_deleteOrders(int floor);

elev_motor_direction_t queue_chooseDirection(Elevator e);

int queue_stopAtFloor(Elevator e);





#endif
