//
// Created by St on 2019-03-26.
//

#include "../data/TableSellingRecord.h"
#include "../data/TablePurchaseRecord.h"
#include "../core/Database.h"
#include "../data/DataManager.h"

#ifndef FRESHMAN_PROJ_C_CONSULTATION_H
#define FRESHMAN_PROJ_C_CONSULTATION_H

Database *AccessoryIn(int type);
Database *AccessoryOut(int type);
Database *Supplier(int sellerId);
Database *Client(int guestId);

#endif //FRESHMAN_PROJ_C_CONSULTATION_H
