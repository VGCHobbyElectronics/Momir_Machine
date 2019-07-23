jasonFileID = 'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\AllSets.json';
textData = textread(jasonFileID, '%c');
decodedJson = jsondecode(textData);
fields = fieldnames(decodedJson);
startingdirectory = dir('C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 0 - RAW FILES');
endingDirectory = {'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\00',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\01',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\02',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\03',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\04',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\05',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\06',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\07',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\08',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\09',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\10',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\11',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\12',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\13',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\14',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\15',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\16',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\17',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\18',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\19',
                    'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\Processing Files\20',}
cardArray = {}
                
                %% Remove white spaces
startingdirectory = startingdirectory(find(~isspace(startingdirectory))),

for i = 1:numel(fields)
    for j = 1:size(decodedJson.(fields{i}).cards)
        if(iscell(decodedJson.(fields{i}).cards))
            if(strfind(decodedJson.(fields{i}).cards{j}.type, 'Creature'))
                if ~any(strcmp(cardArray,decodedJson.(fields{i}).cards{j}.name))
                     cardArray(end+1,:) = {decodedJson.(fields{i}).cards{j}.name, decodedJson.(fields{i}).cards{j}.cmc};
                end
            end
        else
            if(strfind(decodedJson.(fields{i}).cards(j).type, 'Creature'))
                if ~any(strcmp(cardArray,decodedJson.(fields{i}).cards(j).name))
                    cardArray(end+1,:) = {decodedJson.(fields{i}).cards(j).name, decodedJson.(fields{i}).cards(j).cmc};
                end
            end
        end
    end
end

count = 0;

directoryCellArray = struct2cell(startingdirectory);
directoryCellArray = directoryCellArray(1,:);
directoryCellArraySpacesRemoved = regexprep(directoryCellArray,' ','');
directoryCellArraySpacesRemoved = erase(directoryCellArraySpacesRemoved,'pics');
directoryCellArraySpacesRemoved = erase(directoryCellArraySpacesRemoved,'.jpg');

sourceOfFiles = 'C:\Users\Ryan-Work\Desktop\Work Directory\Official Projects\Proj 002 - Momir Box\The Play Ground\Image Processing Play Ground\Offical Processing\Official Files\PHASE 0 - RAW FILES\';

for i = 1:size(cardArray,1)
    
    element = find(strcmp(directoryCellArraySpacesRemoved,cardArray(i,1)));
    
    
    if any(strcmp(directoryCellArraySpacesRemoved,cardArray(i,1)))
       directoryCellArray(element);
       directoryCellArraySpacesRemoved(element);
       filepath = string(strcat(sourceOfFiles,directoryCellArray(element)));
       copyfile(filepath, endingDirectory{cell2mat(cardArray(i,2))+1});
    else
        x = cardArray(i,1);
        count = count + 1;
    end
end
