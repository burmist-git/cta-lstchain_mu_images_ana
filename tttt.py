import pytest

def divide(a, b):
    if b == 0:
        raise ValueError("Denominator cannot be zero")
    return a / b

def test_divide_by_zero():
    #with pytest.raises(ValueError) as exc_info:
        #divide(10, 1)
    assert 0
    
    #print(str(exc_info.value))
    # Now we can assert on the exception message
    #assert "Denominator cannot be zero" in str(exc_info.value)

if __name__ == "__main__":
    test_divide_by_zero()
  
