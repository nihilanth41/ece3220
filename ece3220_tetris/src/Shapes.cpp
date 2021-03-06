#include "Shapes.h"

Shapes::Shapes() { 
// Pieces definition
mShapes = {
	// Square
	{
	{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 1, 1, 0},
	{0, 0, 1, 1, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 1, 1, 0},
	{0, 0, 1, 1, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 1, 1, 0},
	{0, 0, 1, 1, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 1, 1, 0},
	{0, 0, 1, 1, 0},
	{0, 0, 0, 0, 0}
	}
	},
	
	// I
	{
	{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 2, 2, 2, 2},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 2, 0, 0}, 
	{0, 0, 2, 0, 0},
	{0, 0, 2, 0, 0},
	{0, 0, 2, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{2, 2, 2, 2, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 2, 0, 0},
	{0, 0, 2, 0, 0},
	{0, 0, 2, 0, 0},
	{0, 0, 2, 0, 0},
	{0, 0, 0, 0, 0}
	}
	}
	,
	// L
	{
	{
	{0, 0, 0, 0, 0},
	{0, 0, 3, 0, 0},
	{0, 0, 3, 0, 0},
	{0, 0, 3, 3, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 3, 3, 3, 0},
	{0, 3, 0, 0, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 3, 3, 0, 0},
	{0, 0, 3, 0, 0},
	{0, 0, 3, 0, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 3, 0},
	{0, 3, 3, 3, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}
	}
	},
	// L mirrored
	{
	{
	{0, 0, 0, 0, 0},
	{0, 0, 4, 0, 0},
	{0, 0, 4, 0, 0},
	{0, 4, 4, 0, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 4, 0, 0, 0},
	{0, 4, 4, 4, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 4, 4, 0},
	{0, 0, 4, 0, 0},
	{0, 0, 4, 0, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 4, 4, 4, 0},
	{0, 0, 0, 4, 0},
	{0, 0, 0, 0, 0}
	}
	},
	// N
	{
	{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 5, 0},
	{0, 0, 5, 5, 0},
	{0, 0, 5, 0, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 5, 5, 0, 0},
	{0, 0, 5, 5, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 5, 0, 0},
	{0, 5, 5, 0, 0},
	{0, 5, 0, 0, 0},
	{0, 0, 0, 0, 0}
	},
	
	
	
	{
	{0, 0, 0, 0, 0},
	{0, 5, 5, 0, 0},
	{0, 0, 5, 5, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}
	}
	},
	// N mirrored
	{
	{
	{0, 0, 0, 0, 0},
	{0, 0, 6, 0, 0},
	{0, 0, 6, 6, 0},
	{0, 0, 0, 6, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 6, 6, 0},
	{0, 6, 6, 0, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 6, 0, 0, 0},
	{0, 6, 6, 0, 0},
	{0, 0, 6, 0, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 6, 6, 0},
	{0, 6, 6, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}
	}
	},
	// T
	{
	{
	{0, 0, 0, 0, 0},
	{0, 0, 7, 0, 0},
	{0, 0, 7, 7, 0},
	{0, 0, 7, 0, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0},
	{0, 7, 7, 7, 0},
	{0, 0, 7, 0, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 7, 0, 0},
	{0, 7, 7, 0, 0},
	{0, 0, 7, 0, 0},
	{0, 0, 0, 0, 0}
	},
	{
	{0, 0, 0, 0, 0},
	{0, 0, 7, 0, 0},
	{0, 7, 7, 7, 0},
	{0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}
	}
	}
	};	
}
