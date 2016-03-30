// Copyright(c) 2015-2016 Kitti Vongsay
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sub license, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#pragma once

#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace Okonomi
{
    // for DX12ConstantTable::Variable tuple
    constexpr uint_fast32_t CT_VARIABLE_OFFSET = 0;
    constexpr uint_fast32_t CT_VARIABLE_SIZE = 1;

    class DX12ConstantTable
    {
        DX12ConstantTable(const DX12ConstantTable&) = delete;
        DX12ConstantTable& operator=(const DX12ConstantTable&) = delete;
    public:
        DX12ConstantTable() = default;
        DX12ConstantTable(const std::string&, uint_fast32_t);
        DX12ConstantTable(DX12ConstantTable&&);

        DX12ConstantTable& operator=(DX12ConstantTable&&);

        uint_fast32_t getOffset(const std::string&) const;
        inline std::string getName() const { return name_; }
        const uint8_t* getData() const;
        inline uint32_t getSize() const { return static_cast<uint32_t>(data_.size()); }

        template<typename T>
        void setValue(const std::string& name, const T& value)
        {
            auto found = offsetMap_.find(name);

            if (found == offsetMap_.end())
                throw std::invalid_argument("DX12ConstantTable::setValue invalid name");

            auto size = sizeof(T);

            if (size != std::get<CT_VARIABLE_SIZE>(found->second))
                throw std::invalid_argument("DX12ConstantTable::setValue invalid size");

            std::memcpy(&data_.front() + std::get<CT_VARIABLE_OFFSET>(found->second), &value, size);
        }

        template<typename T>
        void setValue(uint_fast32_t offset, const T& value)
        {
            if (offset > size_)
                throw std::invalid_argument("DX12ConstantTable::setValue invalid offset");

            auto size = sizeof(T);

            if (offset + size > size_)
                throw std::out_of_range("DX12ConstantTable::setValue out of bounds");

            std::memcpy(&data_.front() + offset, &value, size);
        }

    private:
        void addVariable(const std::string&, uint_fast32_t, uint_fast32_t);

    private:
        using Variable = std::tuple<uint_fast32_t, uint_fast32_t>;

        std::string name_;
        uint_fast32_t size_;
        std::vector<uint8_t> data_;
        std::unordered_map<std::string, Variable> offsetMap_;     // not thread-safe but should be ok

        friend class DX12ShaderParser;
    };
} // namespace Okonomi