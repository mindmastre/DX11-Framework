#ifndef NAMESPACE_UTILITIES_INCLUDED
#define NAMESPACE_UTILITIES_INCLUDED

#include <xnamath.h>
#include <D3DX10math.h>

namespace Utilities
{
	D3DXMATRIX ConvertXMMatrix(XMMATRIX* input)
	{
		D3DXMATRIX converted;
		D3DXMATRIX newMatrix = D3DXMATRIX(
			input->_11, input->_12, input->_13, input->_14,
			input->_21, input->_22, input->_23, input->_24,
			input->_31, input->_32, input->_33, input->_34,
			input->_41, input->_42, input->_43, input->_44);

		return newMatrix;
	}

	XMMATRIX ConvertD3DMatrix(D3DXMATRIX* input)
	{
		XMMATRIX converted;
		XMMATRIX newMatrix = XMMATRIX(
			input->_11, input->_12, input->_13, input->_14,
			input->_21, input->_22, input->_23, input->_24,
			input->_31, input->_32, input->_33, input->_34,
			input->_41, input->_42, input->_43, input->_44);

		return newMatrix;
	}
}

#endif // NAMESPACE_H_INCLUDED
