#pragma once

namespace mn
{
    enum class DistanceMetric
    {
        /// sqrt(sum((x - y)^2))
        Euclidean,
        /// sum(|x - y|)
        Manhattan,
        /// max(|x - y|)
        Chebyshev
    };
}
