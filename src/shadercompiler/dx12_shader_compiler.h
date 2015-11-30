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

#pragma once

#pragma comment(lib, "ShaderCompiler.lib")

#include <d3d12.h>
#include <future>
#include <string>

namespace Okonomi
{
    // undef the one from math.h
#undef DOMAIN

    enum class EShaderType
    {
        COMPUTE,
        DOMAIN,
        GEOMETRY,
        HULL,
        PIXEL,
        VERTEX
    };

    struct ShaderDesc
    {
        ShaderDesc() noexcept;

        std::string name;
        EShaderType type;
        std::string path;
        std::string entry;
        bool debug;
    };

    class DX12ShaderCompiler
    {
        DX12ShaderCompiler(const DX12ShaderCompiler&) = delete;
        DX12ShaderCompiler& operator=(const DX12ShaderCompiler&) = delete;
        DX12ShaderCompiler(DX12ShaderCompiler&&) = delete;
        DX12ShaderCompiler& operator=(DX12ShaderCompiler&&) = delete;

    public:
        DX12ShaderCompiler() = default;

        D3D12_SHADER_BYTECODE compileShader(const std::string& source, const ShaderDesc&);
        std::future<D3D12_SHADER_BYTECODE> compileShaderAsync(const std::string& source, const ShaderDesc&);

    private:
        std::string getDXShaderType(EShaderType);
    };
} // namespace Okonomi