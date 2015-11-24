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

#include "dx12_shader_parser.h"

#include <D3Dcompiler.h>

#include "utility.h"

namespace Okonomi
{
    auto DX12ShaderParser::ParseShader(const D3D12_SHADER_BYTECODE& bc) -> ResultType
    {
        ResultType res;

        // use reflection to extract bind info
        ID3D12ShaderReflection* reflect = nullptr;
        D3D12_SHADER_DESC progDesc;

        D3DReflect(bc.pShaderBytecode, bc.BytecodeLength, IID_PPV_ARGS(&reflect));
        reflect->GetDesc(&progDesc);

        res.cbuffers = parseConstantBuffers(reflect, progDesc);

        return res;
    }

    std::vector<DX12ConstantTable> DX12ShaderParser::parseConstantBuffers(ID3D12ShaderReflection* reflect, const D3D12_SHADER_DESC& progDesc)
    {
        std::vector<DX12ConstantTable> cbuffers;

        LOG << "Number of constant buffers " << progDesc.ConstantBuffers << std::endl;

        cbuffers.reserve(progDesc.ConstantBuffers);

        for (uint_fast32_t i = 0; i < progDesc.ConstantBuffers; ++i) {
            auto cb = reflect->GetConstantBufferByIndex(i);
            D3D12_SHADER_BUFFER_DESC cbDesc;

            cb->GetDesc(&cbDesc);

            switch (cbDesc.Type) {
                case D3D_CBUFFER_TYPE::D3D10_CT_CBUFFER:
                {
                    LOG << "Constant buffer : " << cbDesc.Name << std::endl;

                    DX12ConstantTable ct{ cbDesc.Name, cbDesc.Size };

                    for (uint_fast32_t j = 0; j < cbDesc.Variables; ++j) {
                        auto var = cb->GetVariableByIndex(j);

                        D3D12_SHADER_VARIABLE_DESC vardesc;

                        var->GetDesc(&vardesc);
                        LOG << "CB var : " << vardesc.Name << ", Offset: " << vardesc.StartOffset << ", Size: " << vardesc.Size << std::endl;

                        ct.addVariable(vardesc.Name, vardesc.StartOffset, vardesc.Size);
                    }

                    cbuffers.push_back(std::move(ct));
                }
                break;

                case D3D_CBUFFER_TYPE::D3D_CT_RESOURCE_BIND_INFO:
                {
                    LOG << "Resource bind info : " << cbDesc.Name << std::endl;
                }
                break;

                default:
                    LOG << cbDesc.Type << std::endl;
                    break;
            }
        }

        return cbuffers;
    }
} // namespace Okonomi