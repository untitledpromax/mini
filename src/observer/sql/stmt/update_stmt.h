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

#pragma once

#include "rc.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/filter_stmt.h"

class Table;

class UpdateStmt : public Stmt
{
public:

  UpdateStmt() = default;
  UpdateStmt(Table *table, Value *values, int value_amount);
  UpdateStmt(Table *table, const Value *values, const char *attribute_name, const size_t condition_num,
     const Condition *conditions, int value_amount);
  UpdateStmt(Table *table, const Value *values, FilterStmt* filter_stmt);
  StmtType type() const override {
    return StmtType::UPDATE;
  }

public:
  static RC create(Db *db, const Updates &update_sql, Stmt *&stmt);

public:
  Table *table() const {return table_;}
  const Value *values() const { return values_; }
  int value_amount() const { return value_amount_; }
  const char *attribute_name() const {return attribute_name_;}
  const size_t condition_num() const {return condition_num_;}
  const Condition *conditions() const {return conditions_;}
  int *updated_count(){return &updated_count_;}
  FilterStmt *filter_stmt() const {return filter_stmt_;}

private:
  Table *table_ = nullptr;
  const Value *values_ = nullptr;
  const char *attribute_name_ = nullptr;
  const size_t condition_num_ = 0;
  const Condition *conditions_ = nullptr;
  int updated_count_ = 0;
  int value_amount_ = 0;
  FilterStmt *filter_stmt_ = nullptr;
};

