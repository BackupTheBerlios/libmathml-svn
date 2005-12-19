#ifndef MATHENUMS_H
#define MATHENUMS_H

namespace linebreak {
	enum Linebreak {
		AUTO,
		NEWLINE,
		INDENTINGNEWLINE,
		NOBREAK,
		GOODBREAK,
		BADBREAK
	};
}
extern const char *linebreaknames[6];
namespace form {
	enum Form {
		PREFIX,
		INFIX,
		POSTFIX
	};
}
extern const char *formnames[3];
namespace closure {
	enum Closure {
		CLOSED,
		OPEN,
		OPEN_CLOSED,
		CLOSED_OPEN
	};
}
extern const char *closurenames[4];
namespace frame {
	enum Frame {
		NONE,
		SOLID,
		DASHED
	};
}
extern const char *framenames[3];
namespace notation {
	enum Notation {
		ACTUARIAL,
		LONGDIV,
		RADICAL
	};
}
extern const char *notationnames[3];
namespace display {
	enum Display {
		BLOCK,
		INLINE
	};
}
extern const char *displaynames[2];
namespace occurrence {
	enum Occurrence {
		PREFIX,
		INFIX,
		FUNCTION_MODEL
	};
}
extern const char *occurrencenames[3];
namespace mathvariant {
	enum Mathvariant {
		NORMAL,
		BOLD,
		ITALIC,
		BOLD_ITALIC,
		DOUBLE_STRUCK,
		BOLD_FRAKTUR,
		SCRIPT,
		BOLD_SCRIPT,
		FRAKTUR,
		SANS_SERIF,
		BOLD_SANS_SERIF,
		SANS_SERIF_ITALIC,
		SANS_SERIF_BOLD_ITALIC,
		MONOSPACE
	};
}
extern const char *mathvariantnames[14];
namespace side {
	enum Side {
		LEFT,
		RIGHT,
		LEFTOVERLAP,
		RIGHTOVERLAP
	};
}
extern const char *sidenames[4];
namespace order {
	enum Order {
		LEXICOGRAPHIC,
		NUMERIC
	};
}
extern const char *ordernames[2];
namespace type {
	enum Type {
		INTEGER,
		RATIONAL,
		REAL,
		COMPLEX_CARTESIAN,
		COMPLEX_POLAR,
		CONSTANT
	};
}
extern const char *typenames[6];
namespace edge {
	enum Edge {
		LEFT,
		RIGHT
	};
}
extern const char *edgenames[2];
namespace overflow {
	enum Overflow {
		SCROLL,
		ELIDE,
		TRUNCATE,
		SCALE
	};
}
extern const char *overflownames[4];
namespace groupalign {
	enum Groupalign {
		LEFT,
		CENTER,
		RIGHT,
		DECIMALPOINT
	};
}
extern const char *groupalignnames[4];

#endif
