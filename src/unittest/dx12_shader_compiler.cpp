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
#include <shadercompiler/dx12_shader_compiler.h>

#include "utility.h"

TEST(ShaderCompiler, BadDescEntry)
{
	auto data = Loadfile(L"data/SimpleVS.hlsl");

	Okonomi::DX12ShaderCompiler compiler;

	Okonomi::ShaderDesc desc;

	desc.name = "SimpleVS";
	desc.path = "data/SimpleVS.hlsl";
	desc.type = Okonomi::EShaderType::VERTEX;
	desc.entry = "test";

	auto lambda = [&]() {
		compiler.compileShader(data, desc);
	};

	ASSERT_ANY_THROW(lambda());
}

TEST(ShaderCompiler, BadDescEntryAsync)
{
	auto data = Loadfile(L"data/SimpleVS.hlsl");

	Okonomi::DX12ShaderCompiler compiler;

	Okonomi::ShaderDesc desc;

	desc.name = "SimpleVS";
	desc.path = "data/SimpleVS.hlsl";
	desc.type = Okonomi::EShaderType::VERTEX;
	desc.entry = "test";

	auto lambda = [&]() {
		auto res = compiler.compileShaderAsync(data, desc);

		res.get();
	};

	ASSERT_ANY_THROW(lambda());
}

TEST(ShaderCompiler, BadDescType)
{
	auto data = Loadfile(L"data/SimpleVS.hlsl");

	Okonomi::DX12ShaderCompiler compiler;

	Okonomi::ShaderDesc desc;

	desc.name = "SimpleVS";
	desc.path = "data/SimpleVS.hlsl";
	desc.type = Okonomi::EShaderType::PIXEL;
	desc.entry = "main";

	auto lambda = [&]() {
		compiler.compileShader(data, desc);
	};

	ASSERT_ANY_THROW(lambda());
}

TEST(ShaderCompiler, BadDescTypeAsync)
{
	auto data = Loadfile(L"data/SimpleVS.hlsl");

	Okonomi::DX12ShaderCompiler compiler;

	Okonomi::ShaderDesc desc;

	desc.name = "SimpleVS";
	desc.path = "data/SimpleVS.hlsl";
	desc.type = Okonomi::EShaderType::PIXEL;
	desc.entry = "main";

	auto lambda = [&]() {
		auto res = compiler.compileShaderAsync(data, desc);

		res.get();
	};

	ASSERT_ANY_THROW(lambda());
}

TEST(ShaderCompiler, CompileVS)
{
	auto data = Loadfile(L"data/SimpleVS.hlsl");

	Okonomi::DX12ShaderCompiler compiler;

	Okonomi::ShaderDesc desc;

	desc.name = "SimpleVS";
	desc.path = "data/SimpleVS.hlsl";
	desc.type = Okonomi::EShaderType::VERTEX;
	desc.entry = "main";

	ASSERT_NO_THROW({
		auto res = compiler.compileShader(data, desc);
	});
}

TEST(ShaderCompiler, CompilePS)
{
	auto data = Loadfile(L"data/SimplePS.hlsl");

	Okonomi::DX12ShaderCompiler compiler;

	Okonomi::ShaderDesc desc;

	desc.name = "SimplePS";
	desc.path = "data/SimplePS.hlsl";
	desc.type = Okonomi::EShaderType::PIXEL;
	desc.entry = "main";

	ASSERT_NO_THROW({
		auto res = compiler.compileShader(data, desc);
	});
}
