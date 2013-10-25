dtime = 0

function start()
   print( 'Start state' )
end

function update( dt )
   dtime = dtime + dt
   print( 'Update state ' .. dt .. ' and ' .. dtime )
   if dtime > 1 then
      engine.newstate( 'test2' )
      dtime = 0
   end
end

function stop()
   print( 'Stop state' )
end
