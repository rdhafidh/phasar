/******************************************************************************
 * Copyright (c) 2017 Philipp Schubert.
 * All rights reserved. This program and the accompanying materials are made
 * available under the terms of LICENSE.txt.
 *
 * Contributors:
 *     Philipp Schubert and others
 *****************************************************************************/

/*
 * DynamicSummaries.h
 *
 *  Created on: 08.05.2017
 *      Author: philipp
 */

#ifndef SRC_ANALYSIS_IFDS_IDE_IFDSSUMMARYPOOL_H_
#define SRC_ANALYSIS_IFDS_IDE_IFDSSUMMARYPOOL_H_

#include <algorithm>
#include <memory>
#include <phasar/Config/ContainerConfiguration.h>
#include <phasar/PhasarLLVM/IfdsIde/FlowFunction.h>
#include <phasar/PhasarLLVM/IfdsIde/FlowFunctions/GenAll.h>
#include <phasar/PhasarLLVM/IfdsIde/IFDSSummary.h>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace psr {

template <typename D, typename N> class IFDSSummaryPool {
private:
  /// Stores the summary that starts at a given node.
  std::map<N, std::map<std::vector<bool>, IFDSSummary<D, N>>> SummaryMap;

public:
  IFDSSummaryPool() = default;
  ~IFDSSummaryPool() = default;

  void insertSummary(N StartNode, std::vector<bool> Context,
                     IFDSSummary<D, N> Summary) {
    SummaryMap[StartNode][Context] = Summary;
  }

  bool containsSummary(N StartNode) { return SummaryMap.count(StartNode); }

  std::set<D> getSummary(N StartNode, std::vector<bool> Context) {
    return SummaryMap[StartNode][Context];
  }

  void print() {
    std::cout << "DynamicSummaries:\n";
    for (auto &entry : SummaryMap) {
      std::cout << "Function: " << entry.first << "\n";
      for (auto &context_summaries : entry.second) {
        std::cout << "Context: ";
        for_each(context_summaries.first.begin(), context_summaries.first.end(),
                 [](bool b) { std::cout << b; });
        std::cout << "\n";
        std::cout << "Beg results:\n";
        for (auto &result : context_summaries.second) {
          // result->dump();
          std::cout << "fixme\n";
        }
        std::cout << "End results!\n";
      }
    }
  }
};

} // namespace psr

#endif
