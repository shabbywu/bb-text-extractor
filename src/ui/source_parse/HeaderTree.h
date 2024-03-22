#pragma once
#include "Tree.h"
#include "Sources.h"

namespace SourceParse
{

    using HeaderTree = Tree<LineWithTag>;

    HeaderTree makeHeaderTree(
        const LinesWithTags& linesWithTags,
        const LineWithTag& treeTopLeaf = { -1, "Table Of Content", -1} );

} // namespace SourceParse
