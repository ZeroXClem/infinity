//
// Created by jinhai on 23-6-4.
//

#pragma once

#include <utility>

#include "storage/meta/entry/db_entry.h"
#include "storage/data_block.h"
#include "storage/meta/entry/table_entry.h"

namespace infinity {

class TxnTableStore {
public:
    explicit
    TxnTableStore(String table_name, TableEntry* table_entry, void* txn)
        : table_name_(std::move(table_name)), table_entry_(table_entry), txn_(txn) {}

    UniquePtr<String>
    Append(const SharedPtr<DataBlock>& input_block);

    UniquePtr<String>
    Delete(const Vector<RowID>& row_ids);

    UniquePtr<String>
    Commit();

    Vector<SharedPtr<DataBlock>> blocks_;

    SizeT current_block_id_{0};

    String table_name_{};
    TableEntry* table_entry_{};
    void* txn_{};
};

}
