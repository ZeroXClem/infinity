//
// Created by JinHai on 2022/7/28.
//

#pragma once

#include "executor/physical_operator.h"

namespace infinity {
class PhysicalDropView : public PhysicalOperator {
public:
    explicit
    PhysicalDropView(SharedPtr<String> schema_name,
                     SharedPtr<String> view_name,
                     ConflictType conflict_type,
                     u64 id)
            : PhysicalOperator(PhysicalOperatorType::kDropView, nullptr, nullptr, id),
              schema_name_(std::move(schema_name)),
              view_name_(std::move(view_name)),
              conflict_type_(conflict_type)
            {}

    ~PhysicalDropView() override = default;

    void
    Init() override;

    void
    Execute(SharedPtr<QueryContext>& query_context) override;

    inline SharedPtr<String>
    schema_name() const {
        return schema_name_;
    }

    inline SharedPtr<String>
    view_name() const {
        return view_name_;
    }

    inline ConflictType
    conflict_type() const {
        return conflict_type_;
    }

private:
    SharedPtr<String> schema_name_{};
    SharedPtr<String> view_name_{};
    ConflictType conflict_type_{ConflictType::kInvalid};
};

}
