//
// FlowCV Node Properties
//

#include "Properties.hpp"

#include "imgui.h"
#include "imgui_instance_helper.hpp"

namespace FlowCV {

FlowCV_Properties::FlowCV_Properties()
{
    props_ = std::make_shared<std::vector<DataStruct>>();
    has_changes_ = false;
}

void FlowCV_Properties::AddBool(std::string &&key, std::string &&desc, bool value, bool visible)
{
    DataStruct d;
    d.data_type = PropertyDataTypes::kDataTypeBool;
    d.w_val = std::vector<uint8_t>(sizeof(bool), 0);
    d.r_val = std::vector<uint8_t>(sizeof(bool), 0);
    d.d_val = std::vector<uint8_t>(sizeof(bool), 0);
    *reinterpret_cast<bool *>(d.w_val.data()) = value;
    *reinterpret_cast<bool *>(d.r_val.data()) = value;
    *reinterpret_cast<bool *>(d.d_val.data()) = value;
    d.changed = false;
    d.visibility = visible;
    d.desc = desc;
    d.key = key;
    props_->emplace_back(std::move(d));
    prop_idx[key] = static_cast<int>(props_->size()) - 1;
}

void FlowCV_Properties::AddInt(std::string &&key, std::string &&desc, int value, int min, int max,
                               float step, bool visible)
{
    DataStruct d;
    d.data_type = PropertyDataTypes::kDataTypeInt;
    d.w_val = std::vector<uint8_t>(sizeof(int), 0);
    d.r_val = std::vector<uint8_t>(sizeof(int), 0);
    d.d_val = std::vector<uint8_t>(sizeof(int), 0);
    d.range.min = std::vector<uint8_t>(sizeof(int), 0);
    d.range.max = std::vector<uint8_t>(sizeof(int), 0);
    d.range.step = std::vector<uint8_t>(sizeof(float), 0);
    *reinterpret_cast<int *>(d.w_val.data()) = value;
    *reinterpret_cast<int *>(d.r_val.data()) = value;
    *reinterpret_cast<int *>(d.d_val.data()) = value;
    *reinterpret_cast<int *>(d.range.min.data()) = min;
    *reinterpret_cast<int *>(d.range.max.data()) = max;
    *reinterpret_cast<float *>(d.range.step.data()) = step;
    d.changed = false;
    d.visibility = visible;
    d.desc = desc;
    d.key = key;
    props_->emplace_back(std::move(d));
    prop_idx[key] = static_cast<int>(props_->size()) - 1;
}

void FlowCV_Properties::AddFloat(std::string &&key, std::string &&desc, float value, float min,
                                 float max, float step, bool visible)
{
    DataStruct d;
    d.data_type = PropertyDataTypes::kDataTypeFloat;
    d.w_val = std::vector<uint8_t>(sizeof(float), 0);
    d.r_val = std::vector<uint8_t>(sizeof(float), 0);
    d.d_val = std::vector<uint8_t>(sizeof(float), 0);
    d.range.min = std::vector<uint8_t>(sizeof(float), 0);
    d.range.max = std::vector<uint8_t>(sizeof(float), 0);
    d.range.step = std::vector<uint8_t>(sizeof(float), 0);
    *reinterpret_cast<float *>(d.w_val.data()) = value;
    *reinterpret_cast<float *>(d.r_val.data()) = value;
    *reinterpret_cast<float *>(d.d_val.data()) = value;
    *reinterpret_cast<float *>(d.range.min.data()) = min;
    *reinterpret_cast<float *>(d.range.max.data()) = max;
    *reinterpret_cast<float *>(d.range.step.data()) = step;
    d.changed = false;
    d.visibility = visible;
    d.desc = desc;
    d.key = key;
    props_->emplace_back(std::move(d));
    prop_idx[key] = static_cast<int>(props_->size()) - 1;
}

void FlowCV_Properties::AddOption(std::string &&key, std::string &&desc, int value,
                                  std::vector<std::string> options, bool visible)
{
    DataStruct d;
    d.data_type = PropertyDataTypes::kDataTypeOption;
    d.w_val = std::vector<uint8_t>(sizeof(int), 0);
    d.r_val = std::vector<uint8_t>(sizeof(int), 0);
    d.d_val = std::vector<uint8_t>(sizeof(int), 0);
    d.range.min = std::vector<uint8_t>(sizeof(int), 0);
    d.range.max = std::vector<uint8_t>(sizeof(int), 0);
    *reinterpret_cast<int *>(d.w_val.data()) = value;
    *reinterpret_cast<int *>(d.r_val.data()) = value;
    *reinterpret_cast<int *>(d.d_val.data()) = value;
    *reinterpret_cast<int *>(d.range.min.data()) = 0;
    *reinterpret_cast<int *>(d.range.max.data()) = static_cast<int>(options.size());
    d.options.insert(d.options.end(), std::make_move_iterator(options.begin()),
                     std::make_move_iterator(options.end()));
    options.clear();
    d.changed = false;
    d.visibility = visible;
    d.desc = desc;
    d.key = key;
    props_->emplace_back(std::move(d));
    prop_idx[key] = static_cast<int>(props_->size()) - 1;
}

void FlowCV_Properties::Remove(std::string &&key)
{
    if (prop_idx.find(key) != prop_idx.end()) {
        std::lock_guard<std::mutex> lk(mutex_lock_);
        int idx = prop_idx.at(key);
        props_->erase(props_->begin() + idx);
        prop_idx.erase(key);
    }
}

void FlowCV_Properties::RemoveAll()
{
    std::lock_guard<std::mutex> lk(mutex_lock_);
    props_->clear();
    prop_idx.clear();
}

template <typename T>
T FlowCV_Properties::Get(const std::string &key)
{
    T ret{};

    if (prop_idx.find(key) != prop_idx.end()) {
        ret = *(T *)props_->at(prop_idx.at(key)).r_val.data();
    }

    return ret;
}

template <typename T>
T FlowCV_Properties::GetW(const std::string &key)
{
    T ret{};

    if (prop_idx.find(key) != prop_idx.end()) {
        ret = *(T *)props_->at(prop_idx.at(key)).w_val.data();
    }

    return ret;
}

template <typename T>
T *FlowCV_Properties::GetPointer(const std::string &key)
{
    T *prop = nullptr;
    if (prop_idx.find(key) != prop_idx.end()) {
        prop = (T *)props_->at(prop_idx.at(key)).w_val.data();
    }

    return prop;
}

bool FlowCV_Properties::Exists(const std::string &key)
{
    return prop_idx.find(key) != prop_idx.end();
}

bool FlowCV_Properties::Changed(const std::string &key)
{
    if (prop_idx.find(key) != prop_idx.end()) {
        return props_->at(prop_idx.at(key)).changed;
    }

    return false;
}

void FlowCV_Properties::Sync()
{
    if (has_changes_) {
        std::lock_guard<std::mutex> lk(mutex_lock_);
        for (auto &prop : *props_) {
            if (prop.changed) {
                if (prop.data_type == PropertyDataTypes::kDataTypeBool) {
                    *reinterpret_cast<bool *>(prop.r_val.data()) =
                        *reinterpret_cast<bool *>(prop.w_val.data());
                } else if (prop.data_type == PropertyDataTypes::kDataTypeInt) {
                    *reinterpret_cast<int *>(prop.r_val.data()) =
                        *reinterpret_cast<int *>(prop.w_val.data());
                } else if (prop.data_type == PropertyDataTypes::kDataTypeFloat) {
                    *reinterpret_cast<float *>(prop.r_val.data()) =
                        *reinterpret_cast<float *>(prop.w_val.data());
                } else if (prop.data_type == PropertyDataTypes::kDataTypeOption) {
                    *reinterpret_cast<int *>(prop.r_val.data()) =
                        *reinterpret_cast<int *>(prop.w_val.data());
                }
                prop.changed = false;
            }
        }
        has_changes_ = false;
    }
}

std::shared_ptr<std::vector<DataStruct>> FlowCV_Properties::GetAll()
{
    return props_;
}

void FlowCV_Properties::Set(std::string &&key, bool value)
{
    if (prop_idx.find(key) != prop_idx.end()) {
        std::lock_guard<std::mutex> lk(mutex_lock_);
        auto &prop = props_->at(prop_idx.at(key));
        *reinterpret_cast<bool *>(prop.w_val.data()) = value;
        prop.changed = true;
        has_changes_ = true;
    }
}

void FlowCV_Properties::Set(std::string &&key, int value)
{
    if (prop_idx.find(key) != prop_idx.end()) {
        std::lock_guard<std::mutex> lk(mutex_lock_);
        auto &prop = props_->at(prop_idx.at(key));
        *reinterpret_cast<int *>(prop.w_val.data()) = value;
        prop.changed = true;
        has_changes_ = true;
    }
}

void FlowCV_Properties::Set(std::string &&key, float value)
{
    if (prop_idx.find(key) != prop_idx.end()) {
        std::lock_guard<std::mutex> lk(mutex_lock_);
        auto &prop = props_->at(prop_idx.at(key));
        *reinterpret_cast<float *>(prop.w_val.data()) = value;
        prop.changed = true;
        has_changes_ = true;
    }
}

const std::vector<std::string> &FlowCV_Properties::GetOptions(std::string &&key)
{
    static std::vector<std::string> empty;

    if (prop_idx.find(key) != prop_idx.end()) {
        return props_->at(prop_idx.at(key)).options;
    }

    return empty;
}

void FlowCV_Properties::SetMin(std::string &&key, int value)
{
    if (prop_idx.find(key) != prop_idx.end()) {
        *reinterpret_cast<int *>(props_->at(prop_idx.at(key)).range.min.data()) = value;
    }
}

void FlowCV_Properties::SetMax(std::string &&key, int value)
{
    if (prop_idx.find(key) != prop_idx.end()) {
        *reinterpret_cast<int *>(props_->at(prop_idx.at(key)).range.max.data()) = value;
    }
}

void FlowCV_Properties::SetMin(std::string &&key, float value)
{
    if (prop_idx.find(key) != prop_idx.end()) {
        *reinterpret_cast<float *>(props_->at(prop_idx.at(key)).range.min.data()) = value;
    }
}

void FlowCV_Properties::SetMax(std::string &&key, float value)
{
    if (prop_idx.find(key) != prop_idx.end()) {
        *reinterpret_cast<float *>(props_->at(prop_idx.at(key)).range.max.data()) = value;
    }
}

void FlowCV_Properties::SetStep(std::string &&key, float value)
{
    if (prop_idx.find(key) != prop_idx.end()) {
        *reinterpret_cast<float *>(props_->at(prop_idx.at(key)).range.step.data()) = value;
    }
}

void FlowCV_Properties::SetVisibility(std::string &&key, bool show)
{
    if (prop_idx.find(key) != prop_idx.end()) {
        props_->at(prop_idx.at(key)).visibility = show;
    }
}

void FlowCV_Properties::SetDescription(std::string &&key, std::string &&desc)
{
    if (prop_idx.find(key) != prop_idx.end()) {
        props_->at(prop_idx.at(key)).desc = desc;
    }
}

void FlowCV_Properties::SetToDefault(std::string &&key)
{
    if (prop_idx.find(key) != prop_idx.end()) {
        std::lock_guard<std::mutex> lk(mutex_lock_);
        if (props_->at(prop_idx.at(key)).data_type == PropertyDataTypes::kDataTypeBool) {
            *reinterpret_cast<bool *>(props_->at(prop_idx.at(key)).w_val.data()) =
                *reinterpret_cast<bool *>(props_->at(prop_idx.at(key)).d_val.data());
            props_->at(prop_idx.at(key)).changed = true;
        }
        if (props_->at(prop_idx.at(key)).data_type == PropertyDataTypes::kDataTypeInt) {
            *reinterpret_cast<int *>(props_->at(prop_idx.at(key)).w_val.data()) =
                *reinterpret_cast<int *>(props_->at(prop_idx.at(key)).d_val.data());
            props_->at(prop_idx.at(key)).changed = true;
        }
        if (props_->at(prop_idx.at(key)).data_type == PropertyDataTypes::kDataTypeFloat) {
            *reinterpret_cast<float *>(props_->at(prop_idx.at(key)).w_val.data()) =
                *reinterpret_cast<float *>(props_->at(prop_idx.at(key)).d_val.data());
            props_->at(prop_idx.at(key)).changed = true;
        }
        if (props_->at(prop_idx.at(key)).data_type == PropertyDataTypes::kDataTypeOption) {
            *reinterpret_cast<int *>(props_->at(prop_idx.at(key)).w_val.data()) =
                *reinterpret_cast<int *>(props_->at(prop_idx.at(key)).d_val.data());
            props_->at(prop_idx.at(key)).changed = true;
        }
        has_changes_ = true;
    }
}

void FlowCV_Properties::SetAllToDefault()
{
    std::lock_guard<std::mutex> lk(mutex_lock_);
    for (auto &prop : *props_) {
        if (prop.data_type == PropertyDataTypes::kDataTypeBool) {
            *reinterpret_cast<bool *>(prop.w_val.data()) =
                *reinterpret_cast<bool *>(prop.d_val.data());
            prop.changed = true;
        } else if (prop.data_type == PropertyDataTypes::kDataTypeInt) {
            *reinterpret_cast<int *>(prop.w_val.data()) =
                *reinterpret_cast<int *>(prop.d_val.data());
            prop.changed = true;
        } else if (prop.data_type == PropertyDataTypes::kDataTypeFloat) {
            *reinterpret_cast<float *>(prop.w_val.data()) =
                *reinterpret_cast<float *>(prop.d_val.data());
            prop.changed = true;
        } else if (prop.data_type == PropertyDataTypes::kDataTypeOption) {
            *reinterpret_cast<int *>(prop.w_val.data()) =
                *reinterpret_cast<int *>(prop.d_val.data());
            prop.changed = true;
        }
    }
    has_changes_ = true;
}

template <typename T>
T FlowCV_Properties::GetMin(const std::string &key)
{
    T ret{};

    if (prop_idx.find(key) != prop_idx.end()) {
        auto &d = props_->at(prop_idx.at(key));
        if (d.data_type != PropertyDataTypes::kDataTypeBool) {
            ret = *(T *)d.range.min.data();
        }
    }

    return ret;
}

template <typename T>
T FlowCV_Properties::GetMax(const std::string &key)
{
    T ret{};

    if (prop_idx.find(key) != prop_idx.end()) {
        auto &d = props_->at(prop_idx.at(key));
        if (d.data_type != PropertyDataTypes::kDataTypeBool) {
            ret = *(T *)d.range.max.data();
        }
    }

    return ret;
}

template <typename T>
T FlowCV_Properties::GetStep(const std::string &key)
{
    T ret{};

    if (prop_idx.find(key) != prop_idx.end()) {
        auto &d = props_->at(prop_idx.at(key));
        if (d.data_type != PropertyDataTypes::kDataTypeBool) {
            ret = *(T *)d.range.step.data();
        }
    }

    return ret;
}

void FlowCV_Properties::ToJson(nlohmann::json &j)
{
    std::lock_guard<std::mutex> lk(mutex_lock_);
    for (auto &prop : *props_) {
        if (prop.visibility) {
            if (prop.data_type == PropertyDataTypes::kDataTypeBool) {
                j[prop.key] = *reinterpret_cast<bool *>(prop.w_val.data());
            } else if (prop.data_type == PropertyDataTypes::kDataTypeInt) {
                j[prop.key] = *reinterpret_cast<int *>(prop.w_val.data());
            } else if (prop.data_type == PropertyDataTypes::kDataTypeFloat) {
                j[prop.key] = *reinterpret_cast<float *>(prop.w_val.data());
            } else if (prop.data_type == PropertyDataTypes::kDataTypeOption) {
                j[prop.key] = *reinterpret_cast<int *>(prop.w_val.data());
            }
        }
    }
}

void FlowCV_Properties::FromJson(nlohmann::json &j)
{
    std::lock_guard<std::mutex> lk(mutex_lock_);
    for (auto &prop : *props_) {
        if (j.contains(prop.key)) {
            if (prop.data_type == PropertyDataTypes::kDataTypeBool) {
                *reinterpret_cast<bool *>(prop.w_val.data()) = j[prop.key].get<bool>();
                *reinterpret_cast<bool *>(prop.r_val.data()) = j[prop.key].get<bool>();
            } else if (prop.data_type == PropertyDataTypes::kDataTypeInt) {
                *reinterpret_cast<int *>(prop.w_val.data()) = j[prop.key].get<int>();
                *reinterpret_cast<int *>(prop.r_val.data()) = j[prop.key].get<int>();
            } else if (prop.data_type == PropertyDataTypes::kDataTypeFloat) {
                *reinterpret_cast<float *>(prop.w_val.data()) = j[prop.key].get<float>();
                *reinterpret_cast<float *>(prop.r_val.data()) = j[prop.key].get<float>();
            } else if (prop.data_type == PropertyDataTypes::kDataTypeOption) {
                *reinterpret_cast<int *>(prop.w_val.data()) = j[prop.key].get<int>();
                *reinterpret_cast<int *>(prop.r_val.data()) = j[prop.key].get<int>();
            }
        }
    }
}

void FlowCV_Properties::DrawUi(const char *inst_id)
{
    for (auto &prop : *props_) {
        if (prop.visibility) {
            if (prop.data_type == PropertyDataTypes::kDataTypeBool) {
                bool val = *reinterpret_cast<bool *>(prop.w_val.data());
                if (ImGui::Checkbox(CreateControlString(prop.desc.c_str(), inst_id).c_str(),
                                    &val)) {
                    *reinterpret_cast<bool *>(prop.w_val.data()) = val;
                    prop.changed = true;
                    has_changes_ = true;
                }
            } else if (prop.data_type == PropertyDataTypes::kDataTypeInt) {
                int val = *reinterpret_cast<int *>(prop.w_val.data());
                ImGui::SetNextItemWidth(120);
                if (ImGui::DragInt(CreateControlString(prop.desc.c_str(), inst_id).c_str(), &val,
                                   *reinterpret_cast<float *>(prop.range.step.data()),
                                   *reinterpret_cast<int *>(prop.range.min.data()),
                                   *reinterpret_cast<int *>(prop.range.max.data()))) {
                    if (val < *reinterpret_cast<int *>(prop.range.min.data())) {
                        val = *reinterpret_cast<int *>(prop.range.min.data());
                    } else if (val > *reinterpret_cast<int *>(prop.range.max.data())) {
                        val = *reinterpret_cast<int *>(prop.range.max.data());
                    }
                    *reinterpret_cast<int *>(prop.w_val.data()) = val;
                    prop.changed = true;
                    has_changes_ = true;
                }
            } else if (prop.data_type == PropertyDataTypes::kDataTypeFloat) {
                float val = *reinterpret_cast<float *>(prop.w_val.data());
                ImGui::SetNextItemWidth(120);
                if (ImGui::DragFloat(CreateControlString(prop.desc.c_str(), inst_id).c_str(), &val,
                                     *reinterpret_cast<float *>(prop.range.step.data()),
                                     *reinterpret_cast<float *>(prop.range.min.data()),
                                     *reinterpret_cast<float *>(prop.range.max.data()))) {
                    if (val < *reinterpret_cast<float *>(prop.range.min.data())) {
                        val = *reinterpret_cast<float *>(prop.range.min.data());
                    } else if (val > *reinterpret_cast<float *>(prop.range.max.data())) {
                        val = *reinterpret_cast<float *>(prop.range.max.data());
                    }
                    *reinterpret_cast<float *>(prop.w_val.data()) = val;
                    prop.changed = true;
                    has_changes_ = true;
                }
            } else if (prop.data_type == PropertyDataTypes::kDataTypeOption) {
                int val = *reinterpret_cast<int *>(prop.w_val.data());
                ImGui::SetNextItemWidth(140);
                if (ImGui::Combo(
                        CreateControlString(prop.desc.c_str(), inst_id).c_str(), &val,
                        [](void *data, int idx, const char **out_text) {
                            *out_text = (static_cast<const std::vector<std::string> *>(data))
                                            ->at(idx)
                                            .c_str();
                            return true;
                        },
                        (void *)&prop.options, static_cast<int>(prop.options.size()))) {
                    *reinterpret_cast<int *>(prop.w_val.data()) = val;
                    prop.changed = true;
                    has_changes_ = true;
                }
            }
        }
    }
}

// Definitions for template implementations
template bool FlowCV_Properties::Get<bool>(const std::string &key);
template int FlowCV_Properties::Get<int>(const std::string &key);
template float FlowCV_Properties::Get<float>(const std::string &key);
template bool FlowCV_Properties::GetW<bool>(const std::string &key);
template int FlowCV_Properties::GetW<int>(const std::string &key);
template float FlowCV_Properties::GetW<float>(const std::string &key);

template int FlowCV_Properties::GetMin<int>(const std::string &key);
template float FlowCV_Properties::GetMin<float>(const std::string &key);
template int FlowCV_Properties::GetMax<int>(const std::string &key);
template float FlowCV_Properties::GetMax<float>(const std::string &key);
template float FlowCV_Properties::GetStep<float>(const std::string &key);

template bool *FlowCV_Properties::GetPointer<bool>(const std::string &key);
template int *FlowCV_Properties::GetPointer<int>(const std::string &key);
template float *FlowCV_Properties::GetPointer<float>(const std::string &key);

}  // End Namespace FlowCV