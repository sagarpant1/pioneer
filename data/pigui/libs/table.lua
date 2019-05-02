-- Copyright © 2008-2019 Pioneer Developers. See AUTHORS.txt for details
-- Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

local ui = import 'pigui/pigui.lua'

local drawTable = {}

function drawTable.draw(n, id, border, t)
	ui.columns(n, id, border)
	for _, entry in pairs(t) do
		if type(entry) == "table" then
			for i, v in pairs(entry) do
				if (v) then ui.text(v) end
				ui.nextColumn()
			end
		elseif entry == false then
			ui.dummy({x=5, y=ui.getTextLineHeight()})
			ui.nextColumn()
			ui.nextColumn()
		end
	end
	ui.columns(1, "", false)
end

function drawTable.withHeading(name, font, t)
    ui.withFont(font.name, font.size, function()
        ui.text(name)
    end)

    drawTable.draw(table.unpack(t))
end

return drawTable
