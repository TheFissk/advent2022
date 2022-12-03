const fs = require("fs");

fs.readFile("./input.txt", "utf8", (err, data) => {
  const snackInventory = data.split("\r\n\r\n");
  const output = snackInventory.map((elf) =>
    elf.split("\r\n").reduce((total, add) => total + parseInt(add), 0)
  );
  output.sort((a, b) => b - a);
  console.log(output[0] + output[1] + output[2]);
});
