// Copyright(c) 2015 Kitti Vongsay
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

#include <gtest/gtest.h>
#include <DirectXMath.h>

#include <dx12_shader_compiler.h>
#include <dx12_shader_parser.h>

#include "utility.h"

class DX12ConstantTableTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        auto data = Loadfile(L"data/SimpleVS.hlsl");

        Okonomi::DX12ShaderCompiler compiler;

        Okonomi::ShaderDesc desc;

        desc.name = "SimpleVS";
        desc.path = "data/SimpleVS.hlsl";
        desc.type = Okonomi::EShaderType::VERTEX;
        desc.entry = "main";

        auto bc = compiler.compileShader(data, desc);

        Okonomi::DX12ShaderParser parser;

        auto res = parser.ParseShader(bc);

        table_ = std::move(res.cbuffers.front());
    }

protected:
    Okonomi::DX12ConstantTable table_;
};

TEST_F(DX12ConstantTableTest, Valid)
{
    EXPECT_EQ(table_.getName(), "ModelViewProjectionConstantBuffer");
    EXPECT_EQ(table_.getSize(), 256);
    EXPECT_NE(table_.getData(), nullptr);
}

TEST_F(DX12ConstantTableTest, Empty)
{
    Okonomi::DX12ConstantTable ct;

    EXPECT_EQ(ct.getName(), "");
    EXPECT_EQ(ct.getSize(), 0);
    EXPECT_EQ(ct.getData(), nullptr);
}

TEST_F(DX12ConstantTableTest, GetOffset)
{
    EXPECT_EQ(table_.getOffset("model"), 0);
    EXPECT_EQ(table_.getOffset("view"), 64);
    EXPECT_EQ(table_.getOffset("projection"), 128);

    // bad name
    EXPECT_THROW(table_.getOffset("wrong"), std::invalid_argument);
}

TEST_F(DX12ConstantTableTest, SetValueByOffset)
{
    auto modelOffset = table_.getOffset("model");
    auto viewOffset = table_.getOffset("view");
    auto projOffset = table_.getOffset("projection");
    auto mat = DirectX::XMMatrixIdentity();

    EXPECT_NO_THROW(table_.setValue<DirectX::XMMATRIX>(modelOffset, mat));
    EXPECT_NO_THROW(table_.setValue<DirectX::XMMATRIX>(viewOffset, mat));
    EXPECT_NO_THROW(table_.setValue<DirectX::XMMATRIX>(projOffset, mat));

    // this is not correct but should still pass
    EXPECT_NO_THROW(table_.setValue<DirectX::XMMATRIX>(30, mat));

    // bad cases
    EXPECT_THROW(table_.setValue<DirectX::XMMATRIX>(193, mat), std::invalid_argument);
    EXPECT_THROW(table_.setValue<DirectX::XMMATRIX>(190, mat), std::out_of_range);
}

TEST_F(DX12ConstantTableTest, SetValueByString)
{
    auto mat = DirectX::XMMatrixIdentity();

    EXPECT_NO_THROW(table_.setValue<DirectX::XMMATRIX>("model", mat));
    EXPECT_NO_THROW(table_.setValue<DirectX::XMMATRIX>("view", mat));
    EXPECT_NO_THROW(table_.setValue<DirectX::XMMATRIX>("projection", mat));

    // bad name
    EXPECT_THROW(table_.setValue<DirectX::XMMATRIX>("wrong", DirectX::XMMatrixIdentity()), std::invalid_argument);

    // bad value
    EXPECT_THROW(table_.setValue<DirectX::XMFLOAT2>("model", DirectX::XMFLOAT2()), std::invalid_argument);
    EXPECT_THROW(table_.setValue<DirectX::XMFLOAT3>("view", DirectX::XMFLOAT3()), std::invalid_argument);
    EXPECT_THROW(table_.setValue<DirectX::XMFLOAT4>("projection", DirectX::XMFLOAT4()), std::invalid_argument);
}

// this test will invalidate the fixture table_ so keep it last
TEST_F(DX12ConstantTableTest, MoveAssignment)
{
    Okonomi::DX12ConstantTable ct;

    ct = std::move(table_);

    EXPECT_EQ(ct.getName(), "ModelViewProjectionConstantBuffer");
    EXPECT_EQ(ct.getSize(), 256);
    EXPECT_NE(ct.getData(), nullptr);
}