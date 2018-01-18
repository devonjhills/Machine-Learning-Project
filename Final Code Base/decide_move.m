% 0 - blank
% 1 - P1
% 2 - P2

function move = decide_move(board)
    % For diagnostics
    %fileID = fopen('decide_move.log','w');
    %fileID = fopen('decide_move.log','a');
    %fprintf(fileID, '========== NEW INVOCATION ==========\n');
    %fprintf(fileID, '\tinput_board = [');
    %for i = 1:42
    %    fprintf(fileID, '%d ', board(i));
    %end
    %fprintf(fileID, ']\n\t=>    board = [');

    % Get the weights
    load('weights2.mat');
    
    % Map to Neural Net encoding
    for i = 1:42
        if (board(i) == 2)
            board(i) = -1;
        end
    end
    %for i = 1:42
    %    fprintf(fileID, '%d ', board(i));
    %end
    %fprintf(fileID, ']\n');
    
    % Test all possibilities
    move = -1;
    bestPr = -9999;
    for i = 1:7
        %fprintf(fileID, '\n\tTesting position %d with this temp board:\n', i);
        tmp = board;
        col = tmp((6 * (i - 1) + 1):(6 * i));
        height = find(col==0, 1, 'first');
        if (isscalar(height))
            tmp((6 * (i - 1)) + height) = 1;
            %fprintf(fileID, '\t  tmp_board = [');
            %for g = 1:42
            %    fprintf(fileID, '%d ', tmp(g));
            %end
            %fprintf(fileID, ']\n');
            layer1 = activation(winWeights1 * tmp.');
            winPr = activation(winWeights2 * layer1);
            %fprintf(fileID, '\tThe probability is %f\n', winPr);
            if (winPr > bestPr)
                %fprintf(fileID, '\t\tThis is the best so far!\n');
                bestPr = winPr;
                move = i;
            end
        else
            %fprintf(fileID, '\tThis position is not allowed!\n');
        end
    end
    %winPr = pred(board, winWeights1,winWeights2);
    %drawPr = pred(board, drawWeights1, drawWeights2);
    %lossPr = pred(board, lossWeights1, lossWeights2);
    %fprintf(fileID, 'Choosing %d as my move!\n\n', move);
    %fclose(fileID);
end

function x = activation(x)
    x = 1./(1+exp(-x));
end