for i = 0, 70 do
	local v = V(rnd(-5,5),rnd(-5,5),rnd(-5,5))
	v = norm(v);
	local p = v * 20.0
	ent(101 + i, "tree.lua", 0.05, p.x, p.y, p.z, v.x, v.y, v.z);
end

for i = 0, 50 do
	local v = V(rnd(-5,5),rnd(-5,5),rnd(-5,5))
	v = norm(v);
	local p = v * 25.0
	ent(181 + i, "shell.lua", 0.02, p.x, p.y, p.z, v.x, v.y, v.z);
end
