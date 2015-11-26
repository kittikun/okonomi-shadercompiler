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

#include <dx12_shader_compiler.h>
#include <dx12_shader_parser.h>

#include "utility.h"

class DX12ShaderParserTest : public ::testing::Test
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

        bc_ = compiler.compileShader(data, desc);
    }

protected:
    D3D12_SHADER_BYTECODE bc_;
};

TEST_F(DX12ShaderParserTest, Parse)
{
    Okonomi::DX12ShaderParser parser;

    auto res = parser.ParseShader(bc_);

    EXPECT_GT(res.cbuffers.size(), 0);
}