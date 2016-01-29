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

#include <d3d12.h>
#include <D3d12shader.h>
#include <vector>

#include "dx12_constant_table.h"

namespace Okonomi
{
    class DX12ShaderParser
    {
        DX12ShaderParser(const DX12ShaderParser&) = delete;
        DX12ShaderParser& operator=(const DX12ShaderParser&) = delete;
        DX12ShaderParser(DX12ShaderParser&&) = delete;
        DX12ShaderParser& operator=(DX12ShaderParser&&) = delete;
    public:
        DX12ShaderParser() = default;

        struct ResultType
        {
            std::vector<DX12ConstantTable> cbuffers;
        };

        auto ParseShader(const D3D12_SHADER_BYTECODE&)->ResultType;

    private:
        std::vector<DX12ConstantTable> parseConstantBuffers(ID3D12ShaderReflection*, const D3D12_SHADER_DESC&);
    };
} // namespace Okonomi