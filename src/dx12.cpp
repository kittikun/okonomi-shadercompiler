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

#include "dx12.h"

#include <d3dcompiler.h>

namespace Okonomi
{
    void DX12ShaderCompiler::compileShader(const std::string& source, const ShaderDesc& desc)
    {
        ID3DBlob* shaderBlob = nullptr;
        ID3DBlob* errorBlob = nullptr;

        UINT flags = D3DCOMPILE_PACK_MATRIX_COLUMN_MAJOR;

        if (desc.debug)
            flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
        else
            flags |= D3DCOMPILE_OPTIMIZATION_LEVEL3;

        auto hr = D3DCompile(source.c_str(), source.size(), desc.path.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
            desc.entry.c_str(), getDXShaderType(desc.type).c_str(), flags, 0, &shaderBlob, &errorBlob);
    }

    std::string DX12ShaderCompiler::getDXShaderType(EShaderType type)
    {
        std::string res;

        switch (type) {
            case EShaderType::COMPUTE:
                res = "cs_5_1";
                break;
            case EShaderType::DOMAIN:
                res = "ds_5_1";
                break;
            case EShaderType::GEOMETRY:
                res = "gs_5_1";
                break;
            case EShaderType::HULL:
                res = "hs_5_1";
                break;
            case EShaderType::PIXEL:
                res = "ps_5_1";
                break;
            case EShaderType::VERTEX:
                res = "vs_5_1";
                break;

            default:
                throw new std::runtime_error{ "ShaderCompiler::getDXShaderType, unknown type" };
        }

        return res;
    }
} // namespace Okonomi