// Copyright (C) 2019  Joseph Artsimovich <joseph.artsimovich@gmail.com>, 4lex4 <4lex49@zoho.com>
// Use of this source code is governed by the GNU GPLv3 license that can be found in the LICENSE file.

#include "OrderByWidthProvider.h"

#include <utility>

namespace select_content {
OrderByWidthProvider::OrderByWidthProvider(std::shared_ptr<Settings> settings) : m_settings(std::move(settings)) {}

bool OrderByWidthProvider::precedes(const PageId& lhsPage,
                                    const bool lhsIncomplete,
                                    const PageId& rhsPage,
                                    const bool rhsIncomplete) const {
  const std::unique_ptr<Params> lhsParams(m_settings->getPageParams(lhsPage));
  const std::unique_ptr<Params> rhsParams(m_settings->getPageParams(rhsPage));

  QSizeF lhsSize;
  if (lhsParams) {
    lhsSize = lhsParams->contentSizeMM();
  }
  QSizeF rhsSize;
  if (rhsParams) {
    rhsSize = rhsParams->contentSizeMM();
  }

  const bool lhsValid = !lhsIncomplete && lhsSize.isValid();
  const bool rhsValid = !rhsIncomplete && rhsSize.isValid();

  if (lhsValid != rhsValid) {
    // Invalid (unknown) sizes go to the back.
    return lhsValid;
  }
  return lhsSize.width() < rhsSize.width();
}
}  // namespace select_content