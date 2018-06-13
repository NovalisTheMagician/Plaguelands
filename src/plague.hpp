#ifndef PLAGUE_HPP_
#define PLAGUE_HPP_

#include <optional>

#include <vector>
#include <string>
#include <map>

#include <stdint.h>

typedef uint64_t ulong;
typedef uint32_t uint;
typedef uint16_t ushort;
typedef uint8_t byte;

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#endif
