//
// Created by jinhai on 23-6-23.
//

#pragma once

#include <utility>

#include "common/types/internal_types.h"
#include "storage/meta/entry/base_entry.h"
#include "storage/txn/txn_context.h"
#include "storage/table_def.h"

namespace infinity {

class TableMeta {
public:
    explicit
    TableMeta(String name, void* buffer_mgr) : table_name_(std::move(name)), buffer_mgr_(buffer_mgr) {}

    EntryResult
    CreateNewEntry(const SharedPtr<String>& dir,
                   u64 txn_id,
                   TxnTimeStamp begin_ts,
                   TxnContext* txn_context,
                   const SharedPtr<TableDef>& table_def,
                   void* db_entry);

    EntryResult
    DropNewEntry(u64 txn_id, TxnTimeStamp begin_ts, TxnContext* txn_context, const String& table_name, void* db_entry);

    void
    DeleteNewEntry(u64 txn_id, TxnContext* txn_context);

    EntryResult
    GetEntry(u64 txn_id, TxnTimeStamp begin_ts);

private:
    RWMutex rw_locker_{};
    String table_name_{};
    SharedPtr<String> dir_{};
    void* buffer_mgr_{};

    // Ordered by commit_ts from latest to oldest.
    List<UniquePtr<BaseEntry>> entry_list_{};
};

}

