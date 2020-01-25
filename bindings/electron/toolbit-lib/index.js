if(process.platform==='linux') {
  module.exports = require('./lib/toolbit-linux.node');
} else if (process.platform==='darwin') {
  module.exports = require('./lib/toolbit-macos.node');
} else if (process.platform==='win32') {
  module.exports = require('./lib/toolbit-mswin.node');
}
