//
// FlowCV Node Properties
//

#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "Export.hpp"

namespace FlowCV {

///@brief 数据种类
///
enum class PropertyDataTypes
{
    kDataTypeUndefined = 0,
    kDataTypeBool,
    kDataTypeInt,
    kDataTypeFloat,
    kDataTypeOption,
    kDataTypeSeparator
};

///@brief 数据范围
///
struct PropertyValueRange
{
    std::vector<uint8_t> min;
    std::vector<uint8_t> max;
    std::vector<uint8_t> step;
};

///@brief 数据结构
///
struct DataStruct
{
    std::string key;
    PropertyDataTypes data_type;
    std::vector<uint8_t> d_val;
    std::vector<uint8_t> w_val;
    std::vector<uint8_t> r_val;
    PropertyValueRange range;
    std::vector<std::string> options;
    std::string desc;
    bool visibility;
    bool changed;
};

///@brief 属性
///
class FLOW_EDITOR_PUBLIC FlowCV_Properties
{
  public:
    FlowCV_Properties();
    ///@brief 添加bool
    ///
    ///@param key
    ///@param desc
    ///@param value
    ///@param visible
    void AddBool(std::string &&key, std::string &&desc, bool value, bool visible = true);

    ///@brief 添加int
    ///
    ///@param key
    ///@param desc
    ///@param value
    ///@param min
    ///@param max
    ///@param step
    ///@param visible
    void AddInt(std::string &&key, std::string &&desc, int value, int min = 0, int max = 100,
                float step = 0.5F, bool visible = true);

    ///@brief 添加float
    ///
    ///@param key
    ///@param desc
    ///@param value
    ///@param min
    ///@param max
    ///@param step
    ///@param visible
    void AddFloat(std::string &&key, std::string &&desc, float value, float min = 0.0F,
                  float max = 100.0F, float step = 0.1F, bool visible = true);

    ///@brief 添加选项
    ///
    ///@param key
    ///@param desc
    ///@param value
    ///@param options
    ///@param visible
    void AddOption(std::string &&key, std::string &&desc, int value,
                   std::vector<std::string> options, bool visible = true);

    ///@brief 移除
    ///
    ///@param key
    void Remove(std::string &&key);

    ///@brief 移除所有
    ///
    void RemoveAll();

    ///@brief 设置bool值
    ///
    ///@param key
    ///@param value
    void Set(std::string &&key, bool value);

    ///@brief 设置int值
    ///
    ///@param key
    ///@param value
    void Set(std::string &&key, int value);

    ///@brief 设置float值
    ///
    ///@param key
    ///@param value
    void Set(std::string &&key, float value);

    ///@brief 设置int最小值
    ///
    ///@param key
    ///@param value
    void SetMin(std::string &&key, int value);

    ///@brief 设置int最大值
    ///
    ///@param key
    ///@param value
    void SetMax(std::string &&key, int value);

    ///@brief Set the Min object
    ///
    ///@param key
    ///@param value
    void SetMin(std::string &&key, float value);

    ///@brief Set the Max object
    ///
    ///@param key
    ///@param value
    void SetMax(std::string &&key, float value);

    ///@brief Set the Step object
    ///
    ///@param key
    ///@param value
    void SetStep(std::string &&key, float value);

    ///@brief Set the Visibility object
    ///
    ///@param key
    ///@param show
    void SetVisibility(std::string &&key, bool show);

    ///@brief Set the Description object
    ///
    ///@param key
    ///@param desc
    void SetDescription(std::string &&key, std::string &&desc);

    ///@brief Set the To Default object
    ///
    ///@param key
    void SetToDefault(std::string &&key);

    ///@brief Set the All To Default object
    ///
    void SetAllToDefault();

    ///@brief
    ///
    ///@param key
    ///@return true
    ///@return false
    bool Exists(const std::string &key);

    ///@brief
    ///
    ///@param key
    ///@return true
    ///@return false
    bool Changed(const std::string &key);

    ///@brief Get the All object
    ///
    ///@return std::shared_ptr<std::vector<DataStruct>>
    std::shared_ptr<std::vector<DataStruct>> GetAll();

    ///@brief Get the Pointer object
    ///
    ///@tparam T
    ///@param key
    ///@return T*
    template <typename T>
    T *GetPointer(const std::string &key);

    ///@brief
    ///
    ///@tparam T
    ///@param key
    ///@return T
    template <typename T>
    T Get(const std::string &key);

    ///@brief
    ///
    ///@tparam T
    ///@param key
    ///@return T
    template <typename T>
    T GetW(const std::string &key);

    ///@brief Get the Min object
    ///
    ///@tparam T
    ///@param key
    ///@return T
    template <typename T>
    T GetMin(const std::string &key);

    ///@brief Get the Max object
    ///
    ///@tparam T
    ///@param key
    ///@return T
    template <typename T>
    T GetMax(const std::string &key);

    ///@brief Get the Step object
    ///
    ///@tparam T
    ///@param key
    ///@return T
    template <typename T>
    T GetStep(const std::string &key);

    ///@brief
    ///
    ///@param inst_id
    void DrawUi(const char *inst_id);

    ///@brief
    ///
    ///@param j
    void ToJson(nlohmann::json &j);

    ///@brief
    ///
    ///@param j
    void FromJson(nlohmann::json &j);

    ///@brief Get the Options object
    ///
    ///@param key
    ///@return const std::vector<std::string>&
    const std::vector<std::string> &GetOptions(std::string &&key);

    ///@brief
    ///
    void Sync();

  private:
    bool has_changes_;
    std::shared_ptr<std::vector<DataStruct>> props_;
    std::unordered_map<std::string, int> prop_idx;
    std::mutex mutex_lock_;

};  // End Class Node_Properties

}  // End Namespace FlowCV
