/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/update_stmt.h"
#include "update_stmt.h"
#include "storage/common/db.h"
#include "common/log/log.h"

UpdateStmt::UpdateStmt(Table *table, Value *values, int value_amount)
  : table_ (table), values_(values), value_amount_(value_amount)
{}

UpdateStmt::UpdateStmt(Table *table, const Value *values, const char *attribute_name, const size_t condition_num,
    const Condition *conditions, int value_amount)
  : table_ (table), values_(values),  attribute_name_(attribute_name), condition_num_(condition_num),
   conditions_(conditions), value_amount_(value_amount)
{}

RC UpdateStmt::create(Db *db, const Updates &update, Stmt *&stmt)
{
  // TODO
  const char *table_name = update.relation_name;
  Table *table = db->find_table(table_name);

  if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

  stmt = new UpdateStmt(table, &update.value, update.attribute_name, update.condition_num, update.conditions, 1);
  return RC::SUCCESS;
}
